<?php
/**
 * @file
 */

use \CultuurNet\Search\ActivityStatsExtendedEntity;

/**
 * A handler to provide links to operations that can be performed on the item.
 */
class views_handler_field_cdb_item_operations extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  function render($values) {
    /** @var ActivityStatsExtendedEntity $extended_entity */
    $extended_entity = $values;
    $links = array();

    if ($extended_entity->getType() === 'event') {

      // Update and delete
      $ops = array(
        'edit' => array(
          'permission' => 'edit culturefeed events',
          'title' => t('Edit'),
        ),
        'delete' => array(
          'permission' => 'delete culturefeed events',
          'title' => t('Delete'),
        )
      );

      $user = $cf_account = DrupalCultureFeed::getLoggedInUser();
      $udb_permission = user_access('edit culturefeed events') && ($extended_entity->getEntity()->getCreatedBy() == $user->mbox);

      if ($udb_permission) {
        foreach ($ops as $op => $op_details) {
          $path = culturefeed_entry_ui_entity_path($extended_entity, $op);
          if ($path && user_access($op_details['permission'])) {
            $links[$op] = l($op_details['title'], $path);
          }
        }
      }
      else {
        $links[] = '<button class="btn btn-default disabled">' . t('No permission to edit event') . '</button>';
      }

      // Collaboration
      $ops = array(
        'tags' => array(
          'permission' => 'manage object tags',
          'title' => t('Tags'),
        )
      );
      foreach ($ops as $op => $op_details) {
        $path = culturefeed_entry_ui_entity_path($extended_entity, $op);
        if ($path && user_access($op_details['permission'])) {
          $links[$op] = l($op_details['title'], $path);
        }
      }

    }

    if (!empty($links)) {
      return theme('item_list', array('items' => $links));
    }
    else {
      return '';
    }
  }

}
