#include "../include/main.hpp"
#include "../extern/beatsaber-hook/shared/customui/customui.hpp"
CustomUI::TextObject Test;
Il2CppObject* SettingsViewControllerGO;
Il2CppObject* SettingsViewController;
Il2CppObject* Button;
Il2CppObject* PlayButton;
Il2CppObject* LevelDetailViewController;
Il2CppObject* LevelDetailView;
Il2CppObject* ViewController;

void ToggleSettings()
{
    if(ViewController != SettingsViewController)
    {
        ViewController = SettingsViewController;
    }
    else
    {
        ViewController = LevelDetailViewController;
    }
}

MAKE_HOOK_OFFSETLESS(ViewController_DidActivate, void, Il2CppObject* self, bool firstActivation, int activationType) {
    if(firstActivation)
    {
        LevelDetailViewController = il2cpp_utils::GetSystemType("", "StandardLevelDetailViewController");
        SettingsViewControllerGO = *il2cpp_utils::New<Il2CppObject*>(il2cpp_utils::GetClassFromName("UnityEngine", "GameObject"), il2cpp_utils::createcsstr("CustomViewController #1"));
        SettingsViewController = *il2cpp_utils::RunMethod<Il2CppObject*>(SettingsViewControllerGO, "AddComponent", il2cpp_utils::GetSystemType("HMUI", "ViewController"));
    }
    ViewController_DidActivate(self, firstActivation, activationType);
    
    // Don't do stuff like Adding Components here as this code gets activated on each ViewController that runs DidActivate which is a bad thing
    /*if(PlayButton == nullptr)
    PlayButton = *il2cpp_utils::GetFieldValue<Il2CppObject*>(il2cpp_utils::GetClassFromName("", "StandardLevelDetailView"), "_playButton");
    if(ViewController == SettingsViewController)
    {
        Button = *il2cpp_utils::RunMethod<Il2CppObject*>("UnityEngine", "Object", "Instantiate", PlayButton);
            auto PlayButtonTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(PlayButton, "get_transform"));
            auto parent = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(PlayButtonTransform, "get_parent"));
            auto parent2 = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(parent, "get_parent"));
            Il2CppObject* OnClick = *CRASH_UNLESS(il2cpp_utils::GetPropertyValue(Button, "onClick"));
            auto action = il2cpp_utils::MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), nullptr, ToggleSettings);
            il2cpp_utils::RunMethod(OnClick, "AddListener", action);
            auto ButtonTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(Button, "get_transform"));
            il2cpp_utils::RunMethod(ButtonTransform, "SetParent", parent2);
    }
    else
    {
        if(ViewController == LevelDetailViewController)
        {
            Button = *il2cpp_utils::RunMethod<Il2CppObject*>("UnityEngine", "Object", "Instantiate", PlayButton);
            auto PlayButtonTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(PlayButton, "get_transform"));
            auto parent = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(PlayButtonTransform, "get_parent"));
            auto parent2 = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(parent, "get_parent"));
            Il2CppObject* OnClick = *CRASH_UNLESS(il2cpp_utils::GetPropertyValue(Button, "onClick"));
            auto action = il2cpp_utils::MakeAction(il2cpp_functions::class_get_type(il2cpp_utils::GetClassFromName("UnityEngine.Events", "UnityAction")), nullptr, ToggleSettings);
            il2cpp_utils::RunMethod(OnClick, "AddListener", action);
            auto ButtonTransform = *CRASH_UNLESS(il2cpp_utils::RunMethod<Il2CppObject*>(Button, "get_transform"));
            il2cpp_utils::RunMethod(ButtonTransform, "SetParent", parent2);

        }
        
    }*/
}
extern "C" void load() {
    INSTALL_HOOK_OFFSETLESS(ViewController_DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 2));
}
