<?php

/**
 * @file
 * Admin settings for culturefeed_agenda.
 */

/**
 * General settings for culturefeed_agenda.
 */
function culturefeed_agenda_admin_settings_form() {

  $form = array();

  $form['culturefeed_agenda_active_entity_types'] = array(
    '#title' => t('Entity types to be searched'),
    '#type' => 'checkboxes',
    '#options' => culturefeed_agenda_known_entity_types(),
    '#default_value' => variable_get('culturefeed_agenda_active_entity_types', array('event', 'production')),
    '#description' => t('Select the different entity types that can be shown on agenda/search'),
  );

  $form['culturefeed_agenda_enable_activity_links_preprocessing'] = array(
    '#title' => t('Add culturefeed_social links to template variables'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('culturefeed_agenda_enable_activity_links_preprocessing', TRUE),
    '#description' => t('Check this checkbox if you want to have culturefeed_social links in the template variables.'),
  );

  $form['culturefeed_agenda_hide_webresources'] = array(
    '#title' => t('Hide deprecated links stored as mediatype webresource or website'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('culturefeed_agenda_hide_webresources', FALSE),
    '#description' => t('By enabling this the event detail page will only show url\'s in the contactinfo object of cdbxml.'),
  );

  $form['culturefeed_agenda_deduplicate_descriptions'] = array(
    '#title' => t('Remove duplicate short description on detail pages'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('culturefeed_agenda_deduplicate_descriptions', TRUE),
    '#description' => t('By enabling this, the short description on event detail pages will be removed if they are redundant with the long description.'),
  );

  $form['gmap'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('GMAP settings'),
  );

  $form['gmap']['culturefeed_agenda_max_items_per_map'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of items on the map'),
    '#default_value' => variable_get('culturefeed_agenda_max_items_per_map', 700),
  );

  $form['gmap']['culturefeed_agenda_google_maps_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Maps API key'),
    '#default_value' => variable_get('culturefeed_agenda_google_maps_api_key', ''),
  );

  $form = system_settings_form($form);
  $form['#submit'] = array('culturefeed_agenda_admin_settings_form_submit');

  return $form;

}

/**
 * Submit the settings form.
 */
function culturefeed_agenda_admin_settings_form_submit($form, $form_state) {

  $form_state['values']['culturefeed_agenda_active_entity_types'] = array_filter($form_state['values']['culturefeed_agenda_active_entity_types']);
  system_settings_form_submit($form, $form_state);

}

