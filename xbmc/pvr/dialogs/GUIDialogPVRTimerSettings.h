#pragma once
/*
 *      Copyright (C) 2012-2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "pvr/channels/PVRChannel.h" // PVR_INVALID_CHANNEL_UID
#include "settings/dialogs/GUIDialogSettingsManualBase.h"

#include <memory>
#include <vector>
#include <map>

class CFileItem;
class CSetting;

namespace PVR
{
  class CPVRTimerInfoTag;
  typedef std::shared_ptr<CPVRTimerInfoTag> CPVRTimerInfoTagPtr;

  class CPVRTimerType;
  typedef std::shared_ptr<CPVRTimerType> CPVRTimerTypePtr;

  class CGUIDialogPVRTimerSettings : public CGUIDialogSettingsManualBase
  {
  public:
    CGUIDialogPVRTimerSettings();
    virtual ~CGUIDialogPVRTimerSettings();

    void SetTimer(CFileItem *item);

  protected:
    // implementation of ISettingCallback
    virtual void OnSettingChanged(const CSetting *setting);
    virtual void OnSettingAction (const CSetting *setting);

    // specialization of CGUIDialogSettingsBase
    virtual bool AllowResettingSettings() const { return false; }
    virtual void Save();
    virtual void SetupView();

    // specialization of CGUIDialogSettingsManualBase
    virtual void InitializeSettings();
    
  private:
    void InitializeTypesList();
    void InitializeChannelsList();
    void SetButtonLabels();

    static CDateTime InitializeDateTime(const CDateTime &datetime);
    static int  GetDateAsInt(const CDateTime &datetime);
    static void SetDateFromInt(CDateTime &datetime, int date);
    static void SetTimeFromSystemTime(CDateTime &datetime, const SYSTEMTIME &time);

    static void TypesFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void ChannelsFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void DaysFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void DupEpisodesFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void WeekdaysFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void PrioritiesFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void LifetimesFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);
    static void RecordingGroupFiller(
      const CSetting *setting, std::vector< std::pair<std::string, int> > &list, int &current, void *data);

    void AddCondition(
      CSetting *setting, const std::string &identifier, SettingConditionCheck condition,
      SettingDependencyType depType, const std::string &settingId);

    void AddTypeDependentEnableCondition(CSetting *setting, const std::string &identifier);
    static bool TypeReadOnlyCondition(
      const std::string &condition, const std::string &value, const CSetting *setting, void *data);

    void AddTypeDependentVisibilityCondition(CSetting *setting, const std::string &identifier);
    static bool TypeSupportsCondition(
      const std::string &condition, const std::string &value, const CSetting *setting, void *data);

    void AddAnytimeDependentVisibilityCondition(CSetting *setting, const std::string &identifier);
    static bool AnytimeSetCondition(
      const std::string &condition, const std::string &value, const CSetting *setting, void *data);

    typedef std::map<int, CPVRTimerTypePtr>  TypeEntriesMap;

    typedef struct ChannelDescriptor
    {
      int         channelUid;
      int         clientId;
      std::string description;

      ChannelDescriptor(int _channelUid = PVR_INVALID_CHANNEL_UID,
                        int _clientId   = -1,
                        const std::string& _description = "")
      : channelUid(_channelUid),
        clientId(_clientId),
        description(_description)
      {}

      inline bool operator ==(const ChannelDescriptor& right) const
      {
        return (channelUid  == right.channelUid &&
                clientId    == right.clientId   &&
                description == right.description);
      }

    } ChannelDescriptor;

    typedef std::map <int, ChannelDescriptor> ChannelEntriesMap;

    CPVRTimerInfoTagPtr m_timerInfoTag;
    TypeEntriesMap      m_typeEntries;
    ChannelEntriesMap   m_channelEntries;
    std::string         m_timerStartTimeStr;
    std::string         m_timerEndTimeStr;

    CPVRTimerTypePtr    m_timerType;
    bool                m_bIsRadio;
    bool                m_bIsNewTimer;
    bool                m_bTimerActive;
    bool                m_bStartAnytime;
    bool                m_bEndAnytime;
    std::string         m_strTitle;
    std::string         m_strEpgSearchString;
    bool                m_bFullTextEpgSearch;
    ChannelDescriptor   m_channel;
    CDateTime           m_startLocalTime;
    CDateTime           m_endLocalTime;
    unsigned int        m_iWeekdays;
    CDateTime           m_firstDayLocalTime;
    unsigned int        m_iPreventDupEpisodes;
    unsigned int        m_iMarginStart;
    unsigned int        m_iMarginEnd;
    int                 m_iPriority;
    int                 m_iLifetime;
    std::string         m_strDirectory;
    unsigned int        m_iRecordingGroup;
  };
} // namespace PVR
