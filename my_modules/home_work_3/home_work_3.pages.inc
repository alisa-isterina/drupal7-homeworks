<?php

function upload_html() {
  
  global $user;
  
  drupal_add_js(array('uid' => $user->uid, ), 'setting');
  
  $output = '';
  
  ctools_include('modal');
  ctools_include('ajax');
  ctools_modal_add_js();
  
  $select = db_select('file_managed', 'fm');
  $select->fields('fm');

  $files_data = $select->execute()->fetchAll();
  
  $rows = array();
  foreach($files_data as $f_data) {
    $rows[] = array(
      'data' => array(
        $f_data->fid,
        array('data' => $f_data->uid, 'class' => 'hide-td', ),
        $f_data->uri,
        $f_data->status,
        l('Downland', file_create_url($f_data->uri)),
      ),
      'uid' => $f_data->uid,
    );
  }
    
  $variables = array(
    'header' => array(
      t('#'),
      array('data' => t('User Id'), 'class' => 'hide-td', ),
      t('Path'),
      t('Status'),
      t('Link'),
    ),
    'rows' => $rows,
    'attributes' => array('id' => 'file-table'),
  );
  
  $output .= theme('table', $variables);

  $output .= ctools_modal_text_button('Upload file', 'upload/modal', 'Upload file');
   
  return $output;
}

function upload_modal_html() {
  ctools_include('modal');
  ctools_include('ajax');
  
  $form_state = array(
    'ajax' => TRUE,
    'title' => t("Upload form")
  );
  
  $commands = ctools_modal_form_wrapper('_upload_modal_form', $form_state);
    
  if(!empty($form_state['executed'])) {
    $commands = array(
      ctools_modal_command_dismiss(), 
      ctools_ajax_command_reload()
    );
  }
  
  print ajax_render($commands);
  
  exit;
}

function _upload_modal_form() {
  $form = array(
    'upload_field' => array(
      '#title' => t('File'),
      '#type' => 'managed_file',
      '#upload_location' => 'private://home_work_3_upload/',
    ),
    'save' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
  );
  
  return $form;
}

function _upload_modal_form_submit($form, &$form_state) {
  global $user;
  
  $file = file_load($form_state['values']['upload_field']);
  $file->status = FILE_STATUS_PERMANENT;
  
  file_save($file);
  file_usage_add($file, 'user', 'user', $user->uid);
}