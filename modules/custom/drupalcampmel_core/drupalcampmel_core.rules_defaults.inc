<?php
/**
 * @file
 * drupalcampmel_core.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function drupalcampmel_core_default_rules_configuration() {
  $items = array();
  $items['commerce_payment_paypal_wps_da'] = entity_import('rules_config', '{ "commerce_payment_paypal_wps_da" : {
      "LABEL" : "PayPal WPS (Drupal Association)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "DrupalCampMelbourne2015" ],
      "REQUIRES" : [ "commerce_payment" ],
      "ON" : { "commerce_payment_methods" : [] },
      "DO" : [
        { "commerce_payment_enable_paypal_wps" : {
            "commerce_order" : [ "commerce-order" ],
            "payment_method" : { "value" : {
                "method_id" : "paypal_wps",
                "settings" : {
                  "business" : "accounting@association.drupal.org",
                  "currency_code" : "AUD",
                  "allow_supported_currencies" : 0,
                  "language" : "AU",
                  "server" : "live",
                  "payment_action" : "sale",
                  "ipn_logging" : "notification",
                  "receiver_emails" : "",
                  "ipn_create_billing_profile" : 1,
                  "show_payment_instructions" : 0
                }
              }
            }
          }
        }
      ]
    }
  }');
  $items['commerce_ss_ticket_purchased'] = entity_import('rules_config', '{ "commerce_ss_ticket_purchased" : {
      "LABEL" : "Ticket purchased",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "DrupalCampMelbourne2015" ],
      "REQUIRES" : [ "rules", "commerce_ss", "commerce_order", "commerce_payment" ],
      "ON" : { "commerce_payment_order_paid_in_full" : [] },
      "DO" : [
        { "user_add_role" : {
            "account" : [ "commerce-order:owner" ],
            "roles" : { "value" : { "3" : "3" } }
          }
        },
        { "user_unblock" : { "account" : [ "commerce-order:owner" ] } },
        { "LOOP" : {
            "USING" : { "list" : [ "commerce-order:commerce-line-items" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "commerce_ss_decrease_by_line_item" : { "commerce_line_item" : [ "list-item" ] } }
            ]
          }
        },
        { "commerce_order_update_status" : { "commerce_order" : [ "commerce_order" ], "order_status" : "completed" } }
      ]
    }
  }');
  $items['rules_confirm_order_new_submission'] = entity_import('rules_config', '{ "rules_confirm_order_new_submission" : {
      "LABEL" : "Confirm order: New submission",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entityform" ],
            "type" : "entityform",
            "bundle" : { "value" : { "confirm_order" : "confirm_order" } }
          }
        }
      ],
      "DO" : [
        { "user_add_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "3" : "3" } }
          }
        }
      ]
    }
  }');
  $items['rules_contact_new_submission'] = entity_import('rules_config', '{ "rules_contact_new_submission" : {
      "LABEL" : "Contact: New submission",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entityform" ],
            "type" : "entityform",
            "bundle" : { "value" : { "contact" : "contact" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "drupalmelbourne@gmail.com",
            "subject" : "Contact form submission",
            "message" : [ "entityform:field-body" ],
            "from" : "[entityform:field-first-name] [entityform:field-last-name] \\u003C[entityform:field-email-address]\\u003E",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_poll_new_submission'] = entity_import('rules_config', '{ "rules_poll_new_submission" : {
      "LABEL" : "Poll: New submission",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entityform" ],
            "type" : "entityform",
            "bundle" : { "value" : { "poll" : "poll" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "drupalmelbourne@gmail.com",
            "subject" : "Poll form submission",
            "message" : "Camp length (days): [entityform:field-poll-days]\\r\\nCommencement day: [entityform:field-poll-start-day]\\r\\nCodesprint: [entityform:field-poll-codesprint]\\r\\nSession length (minutes): [entityform:field-poll-session-length]\\r\\n\\r\\nComments \\/ Thoughts:\\r\\n[entityform:field-poll-comments]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_session_created_updated'] = entity_import('rules_config', '{ "rules_session_created_updated" : {
      "LABEL" : "Session: Created\\/Updated",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : {
        "node_insert--session" : { "bundle" : "session" },
        "node_update--session" : { "bundle" : "session" }
      },
      "DO" : [
        { "mail" : {
            "to" : [ "site:mail" ],
            "subject" : "A Session has been created or updated",
            "message" : "\\u003Cp\\u003E[node:author] has created\\/updated their session.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u0026nbsp;\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Cstrong\\u003ETitle:\\u003C\\/strong\\u003E \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cstrong\\u003EDescription:\\u003C\\/strong\\u003E\\u003Cbr \\/\\u003E\\r\\n[node:body:value]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_signup_create_notify_user'] = entity_import('rules_config', '{ "rules_signup_create_notify_user" : {
      "LABEL" : "Signup: Create and notify user",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_conditional" ],
      "USES VARIABLES" : { "entityform_submission" : { "label" : "Entityform Submission", "type" : "entityform" } },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entityform-submission" ],
            "type" : "entityform",
            "bundle" : { "value" : { "register_interest" : "register_interest" } }
          }
        }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "user",
              "property" : "mail",
              "value" : [ "entityform-submission:field-email-address" ],
              "limit" : "1"
            },
            "PROVIDE" : { "entity_fetched" : { "user_existing" : "Existing user" } }
          }
        },
        { "CONDITIONAL" : [
            {
              "IF" : { "data_is_empty" : { "data" : [ "user-existing" ] } },
              "DO" : [
                { "entity_create" : {
                    "USING" : {
                      "type" : "user",
                      "param_field_first_name" : [ "entityform-submission:field-first-name" ],
                      "param_field_last_name" : [ "entityform-submission:field-last-name" ],
                      "param_name" : [ "entityform-submission:field-email-address" ],
                      "param_mail" : [ "entityform-submission:field-email-address" ]
                    },
                    "PROVIDE" : { "entity_created" : { "user" : "User" } }
                  }
                },
                { "entity_save" : { "data" : [ "user" ], "immediate" : 1 } }
              ]
            }
          ]
        }
      ]
    }
  }');
  $items['rules_signup_create_notify_user_trigger'] = entity_import('rules_config', '{ "rules_signup_create_notify_user_trigger" : {
      "LABEL" : "Signup: Create and notify user",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entityform" ],
            "type" : "entityform",
            "bundle" : { "value" : { "register_interest" : "register_interest" } }
          }
        }
      ],
      "DO" : [
        { "component_rules_signup_create_notify_user" : { "entityform_submission" : [ "entityform" ] } }
      ]
    }
  }');
  return $items;
}
