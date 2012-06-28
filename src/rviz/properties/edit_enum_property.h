/*
 * Copyright (c) 2008, Willow Garage, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RVIZ_EDIT_ENUM_PROPERTY_H
#define RVIZ_EDIT_ENUM_PROPERTY_H

#include <wx/wx.h>
#include <wx/propgrid/propgrid.h>
/* START_WX-2.9_COMPAT_CODE
This code is related to ticket: https://code.ros.org/trac/ros-pkg/ticket/5157
*/
#if wxMAJOR_VERSION == 2 and wxMINOR_VERSION == 8 // If wxWidgets 2.8.x
// This header has been consolidated in the wx-2.9 version of wxPropgrid
#include <wx/propgrid/propdev.h>
#endif
/* END_WX-2.9_COMPAT_CODE */
#include <wx/propgrid/editors.h>

#include <string>
#include <vector>

#include <boost/function.hpp>

namespace ros
{
class Node;
}

namespace rviz
{

typedef std::vector<std::string> V_string;
typedef boost::function<void(V_string&)> EditEnumOptionCallback;

class EditEnumPGEditor : public wxPGComboBoxEditor
{
  DECLARE_DYNAMIC_CLASS(EditEnumPGEditor);
public:
  EditEnumPGEditor(const EditEnumOptionCallback& cb);
  virtual wxPGWindowList CreateControls(wxPropertyGrid *propgrid, wxPGProperty *property, const wxPoint &pos, const wxSize &size) const;

private:
  EditEnumPGEditor();

  EditEnumOptionCallback option_cb_;
};

class EditEnumPGProperty : public wxEditEnumProperty
{
  DECLARE_DYNAMIC_CLASS(EditEnumPGProperty);
public:

  // Normal property constructor.
  EditEnumPGProperty(const wxString& label, const wxString& name = wxPG_LABEL, const wxString& value = wxEmptyString);

  virtual const wxPGEditor* DoGetEditorClass () const { return new EditEnumPGEditor(option_cb_); }

  void setOptionCallback(const EditEnumOptionCallback& cb) { option_cb_ = cb; }

protected:
  EditEnumPGProperty();

  EditEnumOptionCallback option_cb_;
};

} // namespace rviz

#endif // RVIZ_EDIT_ENUM_PROPERTY_H