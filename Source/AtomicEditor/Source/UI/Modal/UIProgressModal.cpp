// Copyright (c) 2014-2015, THUNDERBEAST GAMES LLC All rights reserved
// Please see LICENSE.md in repository root for license information
// https://github.com/AtomicGameEngine/AtomicGameEngine

#include "AtomicEditor.h"

#include <Atomic/Core/Context.h>
#include "AEEvents.h"

#include "UI/UIMainFrame.h"
#include "UI/Modal/UIProgressModal.h"

#include <TurboBadger/tb_widgets_common.h>
#include <TurboBadger/tb_window.h>
#include <TurboBadger/tb_message_window.h>
#include <TurboBadger/tb_editfield.h>

#include <Atomic/UI/TBUI.h>

using namespace tb;

namespace AtomicEditor
{

/// Construct.
ProgressModal::ProgressModal(Context* context, const String &title, const String &message) :
    AEWidget(context)
    , window_(0)
    , dimmer_(0)
{
    TBUI* tbui = GetSubsystem<TBUI>();
    dimmer_ = new TBDimmer();

    window_ = new TBWindow();
    tbui->LoadResourceFile(window_->GetContentRoot(), "AtomicEditor/editor/ui/progressmodal.tb.txt");

    window_->ResizeToFitContent();
    delegate_->AddChild(window_);

    message_ = delegate_->GetWidgetByIDAndType<TBTextField>(TBIDC("message"));
    assert(message_);

    message_->SetText(message.CString());
    window_->SetText(title.CString());

    Center();
}


/// Destruct.
ProgressModal::~ProgressModal()
{

}

void ProgressModal::SetMessage(const String& message)
{
    message_->SetText(message.CString());
}

void ProgressModal::Center()
{
    TBUI* tbui = GetSubsystem<TBUI>();
    TBRect rect = window_->GetRect();
    TBWidget* root = tbui->GetRootWidget();
    TBRect bounds(0, 0, root->GetRect().w, root->GetRect().h);
    window_->SetRect(rect.CenterIn(bounds).MoveIn(bounds).Clip(bounds));
    delegate_->SetRect(bounds);

}

void ProgressModal::Show()
{
    assert(!dimmer_->GetParent());
    TBUI* tbui = GetSubsystem<TBUI>();
    TBWidget* root = tbui->GetRootWidget();
    root->AddChild(dimmer_);
    root->AddChild(delegate_);

}

void ProgressModal::Hide()
{

    TBUI* tbui = GetSubsystem<TBUI>();
    tbui->GetRootWidget()->SetFocusRecursive(WIDGET_FOCUS_REASON_UNKNOWN);

    if (dimmer_->GetParent())
        dimmer_->GetParent()->RemoveChild(dimmer_);

    if (delegate_->GetParent())
        delegate_->GetParent()->RemoveChild(delegate_);

}



}
