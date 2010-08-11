(function($) {

Drupal.behaviors.WoWArmoryTooltip = {
  attach: function(context) {
    $('.wow-tooltip').each(function() {
      var tooltip_loaded = false;
      var $trigger = $('.trigger', this);

      // attach an empty tooltip right after page is loaded.
      var $info = $(Drupal.settings.WoWArmoryTooltip.wrapper);
      $trigger.after($info);
      $info.css({
        display: 'none',
      })

      $trigger.tooltip({
        tipClass: 'wow-item-tooltip',
        offset: [10, 2],
        effect: 'slide',
        relative: true,

        onShow: function() {
          if (!tooltip_loaded) {
            $.getJSON($trigger.attr('href'), function(response) {
              if (response.status != 0) {
                $('.content', $info).html(response.html);
              }
              else {
                // handle error
              }
            });
            tooltip_loaded = true;
          }
        }

      }).dynamic({
        bottom: {
          direction: 'down',
          bounce: true
        }
      });
    });
  }
}

})(jQuery);
