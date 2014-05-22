(function ($) {
    Drupal.behaviors.SelectRow = {
        attach: function() {
            var userRow = $("#file-table").find("tr[uid="+Drupal.settings.uid+"]");
            userRow.each(function() {
                $(this).css("background", "yellow");
            });
        }
    };
})(jQuery);