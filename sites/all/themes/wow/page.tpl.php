  <div id="page-wrapper" class="container-12">
    <div id="header" class="container-12">
      <?php if ($logo || $site_name): ?>
      <div id="branding" class="grid-9">
        <?php if ($logo): ?>
        <div class="<?php if ($site_name) print 'grid-3 alpha'; else print 'grid-9 alpha omega'; ?>">
          <a title="<?php print $site_name; ?>" href="<?php print base_path(); ?>"><img src="<?php print $logo ?>" alt="<?php print $site_name; ?>" id="logo" /></a>
        </div>
        <?php endif; ?>

        <?php if ($site_name): ?>
        <div id="site-name-and-slogan" class="<?php if ($logo) print 'grid-6 omega'; else print 'grid-9 alpha omega'; ?>">
          <div id="site-name"><?php print $site_name; ?></div>
          <?php if ($site_slogan): ?><div id="site-slogan"><?php print $site_slogan; ?></div><?php endif; ?>
        </div>
        <?php endif; ?>
      </div><!-- #branding -->
      <?php endif; ?>

      <?php if ($primary_nav): ?>
      <div id="primary-nav" class="grid-3">
        <?php print $primary_nav; ?>
        <div class="clear"></div>
      </div>
      <?php endif; ?>

    <div class="clear"></div>
    </div><!-- #header -->


    <!-- display slogan in front page and page title in sub pages -->
    <div class="container-12">
      <div id="highlighted" class="<?php if ($page['highlighted_right']) print 'grid-9'; else print 'grid-12'; ?>">
        <?php if ($title): ?>
        <h1 id="page-title"><?php print $title; ?></h1>
        <?php endif; ?>

        <?php if ($tabs): ?>
        <div id="tabs-wrapper">
          <ul class="tabs primary"><?php print render($tabs) ?></ul>
          <?php if ($tabs2): ?><ul class="tabs secondary"><?php print render($tabs2) ?></ul><?php endif; ?>
        </div>
        <?php endif; ?>

        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>

        <?php if ($messages): ?>
        <div id="messages-wrapper">
          <?php print $messages; ?>
        </div>
        <?php endif; ?>
      </div>

      <?php if ($page['highlighted_right']): ?>
      <div id="highlighted-right" class="grid-3">
        <?php print render($page['highlighted_right']); ?>
      </div>
      <?php endif; ?>

      <div class="clear"></div>
    </div>

    <div class="container-12">
      <div id="main" class="<?php if ($page['right']) print 'grid-9'; else print 'grid-12'; ?>">
        <div id="content">
          <?php print render($page['content']); ?>
        </div>

      </div><!-- #main -->

      <?php if ($page['right']): ?>
      <div id="right" class="grid-3">
        <?php print render($page['right']); ?>
      </div>
      <?php endif; ?>

      <div class="clear"></div>
    </div>

    <?php if ($page['bottom']): ?>
    <div class="container-12">
      <div id="bottom" class="grid-12">
        <?php print render($page['bottom']); ?>
      </div>
    </div>
    <?php endif; ?>

    <?php if ($page['footer']): ?>
    <div class="container-12">
      <div id="footer" class="grid-12">
        <?php print render($page['footer']); ?>
      </div>
    </div>
    <?php endif; ?>

  </div><!-- #page-wrapper -->
