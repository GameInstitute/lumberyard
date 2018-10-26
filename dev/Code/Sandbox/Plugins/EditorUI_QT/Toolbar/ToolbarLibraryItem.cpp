/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#include "stdafx.h"
#include "ToolbarLibraryItem.h"

#include <QtWidgets/QToolBar>
#include <QtCore/QCoreApplication>

CToolbarLibraryItem::CToolbarLibraryItem(QMainWindow* mainWindow)
    : IToolbar(mainWindow, TO_CSTR(CToolbarLibraryItem))
{
    setWindowTitle(QObject::tr("Item"));
}

CToolbarLibraryItem::~CToolbarLibraryItem()
{
}

void CToolbarLibraryItem::init()
{
    QAction* action = nullptr;

    action = createAction("actionItemAdd", QObject::tr("Add"), QObject::tr("Add new item"),                     "itemAdd.png");
    action = createAction("actionItemClone", QObject::tr("Clone"), QObject::tr("Clone library item"),               "itemClone.png");
    action = createAction("actionItemRemove", QObject::tr("Remove"), QObject::tr("Remove item"),                      "itemRemove.png");
    action = createAction("actionItemAssign", QObject::tr("Assign"), QObject::tr("Assign item to selected objects"),  "itemAssign.png");
    insertSeparator(action);
    action = createAction("actionItemGetProperties", QObject::tr("Get Properties"), QObject::tr("Get properties from selection"),    "itemGetProperties.png");
    action = createAction("actionItemReload", QObject::tr("Reload"), QObject::tr("Reload item"),                      "itemReload.png");
}