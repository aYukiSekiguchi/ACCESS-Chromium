// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TESTING_PREF_STORE_H_
#define CHROME_BROWSER_PREFS_TESTING_PREF_STORE_H_
#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/prefs/pref_value_map.h"
#include "chrome/common/persistent_pref_store.h"

// |TestingPrefStore| is a preference store implementation that allows tests to
// explicitly manipulate the contents of the store, triggering notifications
// where appropriate.
class TestingPrefStore : public PersistentPrefStore {
 public:
  TestingPrefStore();
  virtual ~TestingPrefStore();

  // Overriden from PrefStore.
  virtual ReadResult GetValue(const std::string& key,
                              const base::Value** result) const OVERRIDE;
  virtual void AddObserver(PrefStore::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(PrefStore::Observer* observer) OVERRIDE;
  virtual size_t NumberOfObservers() const OVERRIDE;
  virtual bool IsInitializationComplete() const OVERRIDE;

  // PersistentPrefStore overrides:
  virtual ReadResult GetMutableValue(const std::string& key,
                                     base::Value** result) OVERRIDE;
  virtual void ReportValueChanged(const std::string& key) OVERRIDE;
  virtual void SetValue(const std::string& key, base::Value* value) OVERRIDE;
  virtual void SetValueSilently(const std::string& key,
                                base::Value* value) OVERRIDE;
  virtual void RemoveValue(const std::string& key) OVERRIDE;
  virtual bool ReadOnly() const OVERRIDE;
  virtual PersistentPrefStore::PrefReadError ReadPrefs() OVERRIDE;
  virtual void ReadPrefsAsync(ReadErrorDelegate* error_delegate) OVERRIDE;
  virtual void CommitPendingWrite() OVERRIDE {}

  // Marks the store as having completed initialization.
  void SetInitializationCompleted();

  // Used for tests to trigger notifications explicitly.
  void NotifyPrefValueChanged(const std::string& key);
  void NotifyInitializationCompleted();

  // Some convenience getters/setters.
  void SetString(const std::string& key, const std::string& value);
  void SetInteger(const std::string& key, int value);
  void SetBoolean(const std::string& key, bool value);

  bool GetString(const std::string& key, std::string* value) const;
  bool GetInteger(const std::string& key, int* value) const;
  bool GetBoolean(const std::string& key, bool* value) const;

  // Getter and Setter methods for setting and getting the state of the
  // |TestingPrefStore|.
  virtual void set_read_only(bool read_only);

 private:
  // Stores the preference values.
  PrefValueMap prefs_;

  // Flag that indicates if the PrefStore is read-only
  bool read_only_;

  // Flag that indicates if the method WritePrefs was called.
  bool prefs_written_;

  // Whether initialization has been completed.
  bool init_complete_;

  ObserverList<PrefStore::Observer, true> observers_;

  DISALLOW_COPY_AND_ASSIGN(TestingPrefStore);
};

#endif  // CHROME_BROWSER_PREFS_TESTING_PREF_STORE_H_
