// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS2_CLEAR_BROWSER_DATA_HANDLER2_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS2_CLEAR_BROWSER_DATA_HANDLER2_H_
#pragma once

#include "chrome/browser/browsing_data_remover.h"
#include "chrome/browser/prefs/pref_member.h"
#include "chrome/browser/ui/webui/options2/options_ui2.h"

namespace options2 {

// Clear browser data handler page UI handler.
class ClearBrowserDataHandler : public OptionsPageUIHandler,
                                public BrowsingDataRemover::Observer {
 public:
  ClearBrowserDataHandler();
  virtual ~ClearBrowserDataHandler();

  // OptionsPageUIHandler implementation.
  virtual void Initialize() OVERRIDE;

  virtual void GetLocalizedValues(DictionaryValue* localized_strings) OVERRIDE;

  // WebUIMessageHandler implementation.
  virtual void RegisterMessages() OVERRIDE;

 private:
  // Javascript callback to start clearing data.
  void HandleClearBrowserData(const ListValue* value);

  // Callback from BrowsingDataRemover. Closes the dialog.
  virtual void OnBrowsingDataRemoverDone() OVERRIDE;

  // If non-null it means removal is in progress. BrowsingDataRemover takes care
  // of deleting itself when done.
  BrowsingDataRemover* remover_;

  // Keeps track of whether clearing LSO data is supported.
  BooleanPrefMember clear_plugin_lso_data_enabled_;

  DISALLOW_COPY_AND_ASSIGN(ClearBrowserDataHandler);
};

}  // namespace options2

#endif  // CHROME_BROWSER_UI_WEBUI_OPTIONS2_CLEAR_BROWSER_DATA_HANDLER2_H_
