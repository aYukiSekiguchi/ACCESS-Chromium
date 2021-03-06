// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_BROWSER_CHILD_PROCESS_HOST_H_
#define CONTENT_PUBLIC_BROWSER_BROWSER_CHILD_PROCESS_HOST_H_
#pragma once

#include "base/process_util.h"
#include "base/string16.h"
#include "build/build_config.h"
#include "content/common/content_export.h"
#include "content/public/common/process_type.h"
#include "ipc/ipc_message.h"

class CommandLine;
class FilePath;

namespace content {

class BrowserChildProcessHostDelegate;
class ChildProcessHost;
struct ChildProcessData;

// This represents child processes of the browser process, i.e. plugins. They
// will get terminated at browser shutdown.
class CONTENT_EXPORT BrowserChildProcessHost : public IPC::Message::Sender {
 public:
  // Used to create a child process host. The delegate must outlive this object.
  static BrowserChildProcessHost* Create(
      ProcessType type,
      BrowserChildProcessHostDelegate* delegate);

  virtual ~BrowserChildProcessHost() {}

  // Derived classes call this to launch the child process asynchronously.
  virtual void Launch(
#if defined(OS_WIN)
      const FilePath& exposed_dir,
#elif defined(OS_POSIX)
      bool use_zygote,
      const base::environment_vector& environ,
#endif
      CommandLine* cmd_line) = 0;

  virtual const ChildProcessData& GetData() const = 0;

  // Returns the ChildProcessHost object used by this object.
  virtual ChildProcessHost* GetHost() const = 0;

  // Returns the termination status of a child.  |exit_code| is the
  // status returned when the process exited (for posix, as returned
  // from waitpid(), for Windows, as returned from
  // GetExitCodeProcess()).  |exit_code| may be NULL.
  virtual base::TerminationStatus GetTerminationStatus(int* exit_code) = 0;

  // Sets the user-visible name of the process.
  virtual void SetName(const string16& name) = 0;

  // Set the handle of the process. BrowserChildProcessHost will do this when
  // the Launch method is used to start the process. However if the owner
  // of this object doesn't call Launch and starts the process in another way,
  // they need to call this method so that the process handle is associated with
  // this object.
  virtual void SetHandle(base::ProcessHandle handle) = 0;
};

};  // namespace content

#endif  // CONTENT_PUBLIC_BROWSER_BROWSER_CHILD_PROCESS_HOST_H_
