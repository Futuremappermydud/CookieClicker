#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"
#include "../extern/beatsaber-hook/shared/utils/il2cpp-utils.hpp"
using namespace il2cpp_utils;
Il2CppObject* UpgradesButton;
Il2CppObject* GainCookieButton;
Il2CppObject* GainTMPLocalizer;
Il2CppObject* GainTMP;
Il2CppObject* UpgradeTMPLocalizer;
Il2CppObject* UpgradeTMP;
Il2CppObject* Menu;
Il2CppObject* CookieMenu;

Il2CppObject* ReleaseInfo;
Il2CppObject* Promo;
Il2CppObject* Statistics;

int yes;
int Upgrades = 1;
int UpgradeCost = 10;
void Destroy(Il2CppObject* obj)
{
    RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", obj);
}

//W.I.P

Il2CppObject* SoloButtonObj;
Il2CppObject* PartyButtonObj;
Il2CppObject* CampaignButtonObj;
Il2CppObject* HowToPlayButtonObj;
Il2CppObject* PSButtonObj;
Il2CppObject* SButtonObj;
Il2CppObject* QButtonObj;
Il2CppObject* CRButtonObj;

Il2CppObject* ReleaseInfoObj;
Il2CppObject* PromoObj;
Il2CppObject* StatisticsObj;
Il2CppObject* NewSongObj;
Il2CppObject* NewPackObj;

Il2CppObject* HorizontalLayout;
Il2CppObject* UpgradesTableView;

CustomUI::TextObject Header;

Il2CppObject* PromoTransform;

void AddCookie()
{
    yes += Upgrades;
    std::string text = "Cookies: ";
    RunMethod(GainTMP, "set_text", createcsstr(text + std::to_string(yes)));
}
void NotEnoughCookies()
{
    std::string UpText2 = "\n\nYou need " + std::to_string(yes - UpgradeCost) + " More cookies</color></size>";
    std::string UpText = "<size=70%><color=#ff0000>Not Enough cookies!" + UpText2;
    RunMethod(UpgradeTMP, "set_text", createcsstr(UpText));
}
void Upgrade()
{
    if(!(yes >= 10)) 
    {
        NotEnoughCookies();
        return;
    }
    
    UpgradeCost *= 2.3;
    Upgrades++;
    std::string UpText = "<size=65%>Upgrades: </size>";
    std::string UpText2 = "\n\n<size=55%>Costs" + std::to_string(UpgradeCost) + "</size>";
    RunMethod(UpgradeTMP, "set_text", createcsstr(UpText + std::to_string(Upgrades) + UpText2));
}

std::string GetMenuTypeFromBool(bool yes)
{
    if(yes)
    {
        return "Main Menu";
    }
    else
    {
        return "Upgrade Menu";
    }
    
}

void ToggleGameObject(Il2CppObject* GameObject, bool value)
{
        RunMethod(GameObject, "SetActive", value);
}
void ToggleComponent(Il2CppObject* Component, bool value)
{
        SetPropertyValue(Component, "enabled", &value);
}
bool f = false;
void TogglePanel()
{
    f = !f;
    ToggleGameObject(Header.gameObj, f);
    ToggleGameObject(SoloButtonObj, !f);
    ToggleGameObject(PartyButtonObj, !f);
    ToggleGameObject(CampaignButtonObj, !f);
    ToggleGameObject(HowToPlayButtonObj, !f);
    ToggleGameObject(PSButtonObj, !f);
    ToggleGameObject(SButtonObj, !f);
    ToggleGameObject(QButtonObj, !f);
    ToggleGameObject(CRButtonObj, !f);
    if(!fileexists("/sdcard/Android/data/com.beatgames.beatsaber/files/mods/libNoticeBoard.so")) ToggleGameObject(ReleaseInfoObj, !f);
    ToggleGameObject(StatisticsObj, !f);
    ToggleGameObject(PromoObj, !f);
    RunMethod(UpgradeTMP, "set_text", createcsstr(GetMenuTypeFromBool(f)));
    ToggleComponent(HorizontalLayout, !f);
}

void GetButtons(Il2CppObject* self)
{
    Il2CppObject* SoloButton = *GetFieldValue(self, "_soloButton");
    Il2CppObject* PartyButton = *GetFieldValue(self, "_partyButton");
    Il2CppObject* CampaignButton = *GetFieldValue(self, "_campaignButton");
    Il2CppObject* HowToPlayButton = *GetFieldValue(self, "_howToPlayButton");
    Il2CppObject* PlayerSettingsButton = *GetFieldValue(self, "_playerSettingsButton");
    Il2CppObject* SettingsButton = *GetFieldValue(self, "_settingsButton");
    Il2CppObject* QuitButton = *GetFieldValue(self, "_quitButton");
    Il2CppObject* CreditsButton = *GetFieldValue(self, "_creditsButton");
    
    SoloButtonObj = *GetPropertyValue(SoloButton, "gameObject");
    PartyButtonObj = *GetPropertyValue(PartyButton, "gameObject");
    CampaignButtonObj = *GetPropertyValue(CampaignButton, "gameObject");
    HowToPlayButtonObj = *GetPropertyValue(HowToPlayButton, "gameObject");
    PSButtonObj = *GetPropertyValue(PlayerSettingsButton, "gameObject");
    SButtonObj = *GetPropertyValue(SettingsButton, "gameObject");
    QButtonObj = *GetPropertyValue(QuitButton, "gameObject");
    CRButtonObj = *GetPropertyValue(CreditsButton, "gameObject");

    ReleaseInfoObj = *GetPropertyValue(ReleaseInfo, "gameObject");
    PromoObj = *GetPropertyValue(Promo, "gameObject");
    StatisticsObj = *GetPropertyValue(Statistics, "gameObject");
    
}

//End W.I.P

Il2CppObject* PlayerSettings;

MAKE_HOOK_OFFSETLESS(MainMenu, void, Il2CppObject* self, bool firstActivation, int activationType)
{
    MainMenu(self, firstActivation, activationType);
    GetButtons(self);
    Vector3 Pos = {0, 0, 2.6f};
    Vector3 Scale = {1, 1, 1};
    if(!firstActivation)
    {
        Il2CppObject* GainButtonObj = *RunMethod(GainCookieButton, "get_gameObject");
        Il2CppObject* UpButtonObj = *RunMethod(UpgradesButton, "get_gameObject");
        Destroy(GainButtonObj);
        Destroy(UpButtonObj);
    }
    PlayerSettings = *GetFieldValue(self, "_playerSettingsButton");
    auto PlayerSettingsTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod(PlayerSettings, "get_transform"));
    GainCookieButton = *RunMethod("UnityEngine", "Object", "Instantiate", PlayerSettings);
    auto GainButtonTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod(GainCookieButton, "get_transform"));

    Il2CppObject* GainButtonObj2 = *RunMethod(GainCookieButton, "get_gameObject");
    GainTMP = *RunMethod(GainButtonObj2, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    GainTMPLocalizer = *RunMethod(GainButtonObj2, "GetComponentInChildren", GetSystemType("Polyglot", "LocalizedTextMeshProUGUI"));
    if (GainTMPLocalizer != nullptr)
    {
        RunMethod(GetClassFromName("UnityEngine", "Object"), "Destroy", GainTMPLocalizer);
    }
    std::string text = "Cookies: ";
    RunMethod(GainTMP, "set_text", createcsstr(text + std::to_string(yes)));
    auto parent = *CRASH_UNLESS(il2cpp_utils::RunMethod(PlayerSettingsTransform, "get_parent"));
    RunMethod(GainButtonTransform, "SetParent", parent);
    RunMethod(GainButtonTransform, "set_position", Pos);
    RunMethod(GainButtonTransform, "set_localScale", Scale);
    Il2CppObject* OnClick = *CRASH_UNLESS(il2cpp_utils::GetPropertyValue(GainCookieButton, "onClick"));
    auto action = MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), nullptr, AddCookie);
    il2cpp_utils::RunMethod(OnClick, "AddListener", action);
    
    
    //Menu


    UpgradesButton = *RunMethod("UnityEngine", "Object", "Instantiate", PlayerSettings);
    auto UpgradeButtonTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod(UpgradesButton, "get_transform"));

    Il2CppObject* UpgradeButtonObj2 = *RunMethod(UpgradesButton, "get_gameObject");
    UpgradeTMP = *RunMethod(UpgradeButtonObj2, "GetComponentInChildren", GetSystemType("TMPro", "TextMeshProUGUI"));
    Il2CppObject* Image = *RunMethod(UpgradeButtonObj2, "GetComponentInChildren", GetSystemType("UnityEngine.UI", "Image"));
    UpgradeTMPLocalizer = *RunMethod(UpgradeButtonObj2, "GetComponentInChildren", GetSystemType("Polyglot", "LocalizedTextMeshProUGUI"));
    if (UpgradeTMPLocalizer != nullptr)
    {
        Destroy(UpgradeTMPLocalizer);
        //Destroy(Image);
    }
    std::string UpText = "Upgrade Menu";
    RunMethod(UpgradeTMP, "set_text", createcsstr(UpText));
    parent = *CRASH_UNLESS(il2cpp_utils::RunMethod(PlayerSettingsTransform, "get_parent"));
    RunMethod(UpgradeButtonTransform, "SetParent", parent);
    RunMethod(UpgradeButtonTransform, "set_position", Pos);
    RunMethod(UpgradeButtonTransform, "set_localScale", Scale);
    Il2CppObject* UpgradeOnClick = *CRASH_UNLESS(il2cpp_utils::GetPropertyValue(UpgradesButton, "onClick"));
    auto Upgradeaction = MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), nullptr, TogglePanel);
    il2cpp_utils::RunMethod(UpgradeOnClick, "AddListener", Upgradeaction);

    //Panel
    auto parent2 = *CRASH_UNLESS(il2cpp_utils::RunMethod(UpgradeButtonTransform, "get_parent"));

    RunMethod(UpgradeButtonTransform, "SetParent", parent2);
    Header.text = "Cookie Clicker: v0.2";
    Header.parentTransform = parent2;
    Header.fontSize = 8.0f;
    Header.sizeDelta = {0, 100};
    Header.create();
    ToggleGameObject(Header.gameObj, false);
    HorizontalLayout = *RunMethod(parent, "GetComponent", GetSystemType("UnityEngine.UI", "HorizontalLayoutGroup"));

    //Upgrade

}

MAKE_HOOK_OFFSETLESS(Release, void, Il2CppObject* self, bool firstActivation, int activationType)
{
    Release(self, firstActivation, activationType);
    ReleaseInfo = self;
}
MAKE_HOOK_OFFSETLESS(Promotion, void, Il2CppObject* self, bool firstActivation, int activationType)
{
    Promotion(self, firstActivation, activationType);
    Promo = self;
}
MAKE_HOOK_OFFSETLESS(Stats, void, Il2CppObject* self, bool firstActivation, int activationType)
{
    Stats(self, firstActivation, activationType);
    Statistics = self;
}

extern "C" void load() {
    INSTALL_HOOK_OFFSETLESS(MainMenu, FindMethodUnsafe("", "MainMenuViewController", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(Release, FindMethodUnsafe("", "ReleaseInfoViewController", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(Promotion, FindMethodUnsafe("", "PromoViewController", "DidActivate", 2));
    INSTALL_HOOK_OFFSETLESS(Stats, FindMethodUnsafe("", "PlayerStatisticsViewController", "DidActivate", 2));
}
