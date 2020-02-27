#include <shlobj.h>
#include <stdio.h>
#include <shobjidl.h>
#include <objbase.h>
#include <atlbase.h>
#include <string>

/* 
    Reference: https://docs.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-iapplicationactivationmanager-activateapplication
*/

int main()
{

    CComPtr<IApplicationActivationManager> spAppActivationManager;
    DWORD pdwProcessId;

    HRESULT hrResult = S_OK;

    if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {

        // Instantiate IApplicationActivationManager
        hrResult = CoCreateInstance(CLSID_ApplicationActivationManager,
            NULL,
            CLSCTX_LOCAL_SERVER,
            IID_IApplicationActivationManager,
            (LPVOID*)&spAppActivationManager);

        if (SUCCEEDED(hrResult))
        {
            // This call ensures that the app is launched as the foreground window
            hrResult = CoAllowSetForegroundWindow(spAppActivationManager, NULL);

            // Launch the app
            if (SUCCEEDED(hrResult))
            {
                hrResult = spAppActivationManager->ActivateApplication(L"windows.immersivecontrolpanel_cw5n1h2txyewy"
                    L"!microsoft.windows.immersivecontrolpanel",
                    L"page=SettingsPageAppsDefaults"
                    L"&target=SettingsPageAppsDefaultsDefaultAppsListView",
                    AO_NONE,
                    &pdwProcessId);
            }
        }
    }

    CoUninitialize();

    return hrResult;
}
