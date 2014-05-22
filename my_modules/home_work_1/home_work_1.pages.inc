<?php 

function training_menu_html() {
  return t("This is the landing page of the Training module.");
}

function training_menu_custom_access_html() {
  return t("You are authenticated user.");
}

function training_menu_permissioned_html() {
  return t("You have access permissioned.");
}

function training_menu_callback_html() {
  return t("The menu entry for this page is of type MENU_CALLBACK.");
}

function training_menu_tabs_html() {
  return t("This is the \"tabs\" menu entry");
}

function _training_menu_tabs_html($content) {
  return $content;
}

function training_menu_arguments_html($one = NULL, $two = NULL) {
  $output = '';
  if($one) {
    $output .= t("Argument 1 = @one <br/>", array("@one" => $one));
  }
  if($two) {
    $output .= t("Argument 2 = @two", array("@two" => $two));
  }
  
  return $output;
}

function training_menu_placeholder_display_html($arg) {
  return t("<div>@arg</div>", array("@arg" => $arg));
}

function training_menu_default_arg_html($arg) {
  if($arg) {
    return $arg;
  }
  drupal_not_found();
}

function training_theme_html() {
  $variables = array(
    'items' => array(
      l('List', url('training/theme/list', array('absolute' => TRUE, ))), 
      l('Table', url('training/theme/table', array('absolute' => TRUE, ))),
      l('image', url('training/theme/image', array('absolute' => TRUE, ))),
      l('Access', url('training/theme/access', array('absolute' => TRUE, ))),
    ),
    'title' => 'Links to themes',
    'type' => 'ol',
  );
  
  return theme('item_list', $variables);
}

function theme_page_html($page) {
  $output = '';
  if($page == 'list') {
    drupal_goto('training/theme');
  } elseif($page == 'table') {
    $output = _table_html();
  } elseif($page == 'image') {
    $output = _image_html();
  } elseif($page == 'access') {
    $output = _access_html();
  }
  return $output;
}

function _table_html() {
  $variables = array(
    'attributes' => array('id' => 'table-test'),
    'caption' => 'Theme table sample',
    'header' => array(
      t('header 1'),
      t('header 2'), 
      t('header 3'),
    ),
    'rows' => array(
      array(
        'data' => array(
          t('Cell 1'), 
          array('data' => t('Cell 2'), 'colspan' => 2), 
        ),
        'class' => array('rowClass'),
      ),
      array(
        'data' => array(
          t('Cell 1'), 
          array('data' => t('Cell 2'), 'colspan' => 2), 
        ),
        'class' => array('rowClass'),
      ),
      array(
        'data' => array(
          t('Cell 1'), 
          array('data' => t('Cell 2'), 'colspan' => 2), 
        ),
        'class' => array('rowClass'),
      ),
    ),
  );
  
  return theme('table', $variables);
}

function _image_html() {
  
  $image_path = 'modules/image/sample.png ';
  
  $image_1 = theme('image', array(
    'path' => $image_path,
    'attributes' => array('class' => 'simple-image'),
    'width' => '250px',
    'alt' => t('image'),
    'title' => t('image'),
  ));
  
  $image_2= theme('image_style',
    array(
      'style_name' => 'thumbnail',
      'path' => $image_path,
      'getsize' => FALSE,
    )
  );
  $image_3= theme('image_style',
    array(
      'style_name' => 'medium',
      'path' => $image_path,
      'getsize' => FALSE,
    )
  );
  $image_4= theme('image_style',
    array(
      'style_name' => 'large',
      'path' => $image_path,
      'getsize' => FALSE,
    )
  );
  
  $variables = array(
    'items' => array(
      $image_1, $image_2, $image_3, $image_4,
    ),
    'type' => 'ol',
  );
  
  return theme('item_list', $variables);
}

function _access_html() {
  global $user;
    
  $permissionsByRoles = user_role_permissions($user->roles);
    
  $access = FALSE;
  foreach($permissionsByRoles as $permissionsByRole) {
    foreach($permissionsByRole as $permission => $value) {
      if($value && $permission == 'access protected content') {
        $access = TRUE;
        break;
      }
    }
  }
  
  $output = "Custom access inversed for rendered content";
  if($access) {
    $output = "Custom access for rendered content";
  }
  
  return $output;
}