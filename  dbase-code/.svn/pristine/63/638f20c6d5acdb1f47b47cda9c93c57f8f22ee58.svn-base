/////////////////////////////////////////////////////////////////////////////
// Name:        smapi.cpp
// Purpose:     Simple MAPI classes
// Author:      PJ Naughter <pjna@naughter.com>
// Modified by: Julian Smart
// Created:     2001-08-21
// RCS-ID:      $Id: smapi.cpp 35650 2005-09-23 12:56:45Z MR $
// Copyright:   (c) PJ Naughter
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include <wx/log.h>
#include <wx/app.h>

#ifdef __WXMSW__

// mapi.h in Cygwin's include directory isn't a full implementation and is
// not sufficient for this lib. However recent versions of Cygwin also
// have another mapi.h in include/w32api which can be used.

#include <windows.h>
#ifdef xx__CYGWIN__
#include <w32api/mapi.h>
#else
#include <mapi.h>
#endif

#include "smapi.h"

class WXDLLIMPEXP_NETUTILS wxMapiData
{
public:
    wxMapiData()
    {
        m_hSession = 0;
        m_nLastError = 0;
        m_hMapi = NULL;
        m_lpfnMAPILogon = NULL;
        m_lpfnMAPILogoff = NULL;
        m_lpfnMAPISendMail = NULL;
        m_lpfnMAPIResolveName = NULL;
        m_lpfnMAPIFreeBuffer = NULL;
    }

    //Data
    LHANDLE             m_hSession; //Mapi Session handle
    long                m_nLastError; //Last Mapi error value
    HINSTANCE           m_hMapi; //Instance handle of the MAPI dll
    LPMAPILOGON         m_lpfnMAPILogon; //MAPILogon function pointer
    LPMAPILOGOFF        m_lpfnMAPILogoff; //MAPILogoff function pointer
    LPMAPISENDMAIL      m_lpfnMAPISendMail; //MAPISendMail function pointer
    LPMAPIRESOLVENAME   m_lpfnMAPIResolveName; //MAPIResolveName function pointer
    LPMAPIFREEBUFFER    m_lpfnMAPIFreeBuffer; //MAPIFreeBuffer function pointer
};


////////////////////////////////// Implementation /////////////////////////////

wxMapiSession::wxMapiSession()
{
    m_data = new wxMapiData;

    Initialise();
}

wxMapiSession::~wxMapiSession()
{
    //Logoff if logged on
    Logoff();

    //Unload the MAPI dll
    Deinitialise();

    delete m_data;
}

void wxMapiSession::Initialise()
{
    //First make sure the "WIN.INI" entry for MAPI is present aswell
    //as the MAPI32 dll being present on the system
    bool bMapiInstalled = (GetProfileInt(_T("MAIL"), _T("MAPI"), 0) != 0) &&
        (SearchPath(NULL, _T("MAPI32.DLL"), NULL, 0, NULL, NULL) != 0);

    if (bMapiInstalled)
    {
        //Load up the MAPI dll and get the function pointers we are interested in
        m_data->m_hMapi = ::LoadLibrary(_T("MAPI32.DLL"));
        if (m_data->m_hMapi)
        {
            m_data->m_lpfnMAPILogon = (LPMAPILOGON) GetProcAddress(m_data->m_hMapi, "MAPILogon");
            m_data->m_lpfnMAPILogoff = (LPMAPILOGOFF) GetProcAddress(m_data->m_hMapi, "MAPILogoff");
            m_data->m_lpfnMAPISendMail = (LPMAPISENDMAIL) GetProcAddress(m_data->m_hMapi, "MAPISendMail");
            m_data->m_lpfnMAPIResolveName = (LPMAPIRESOLVENAME) GetProcAddress(m_data->m_hMapi, "MAPIResolveName");
            m_data->m_lpfnMAPIFreeBuffer = (LPMAPIFREEBUFFER) GetProcAddress(m_data->m_hMapi, "MAPIFreeBuffer");

            //If any of the functions are not installed then fail the load
            if (m_data->m_lpfnMAPILogon == NULL ||
                m_data->m_lpfnMAPILogoff == NULL ||
                m_data->m_lpfnMAPISendMail == NULL ||
                m_data->m_lpfnMAPIResolveName == NULL ||
                m_data->m_lpfnMAPIFreeBuffer == NULL)
            {
                wxLogDebug(_("Failed to get one of the functions pointer in MAPI32.DLL\n"));
                Deinitialise();
            }
        }
    }
    else
        wxLogDebug(_("Mapi is not installed on this computer\n"));
}

void wxMapiSession::Deinitialise()
{
    if (m_data->m_hMapi)
    {
        //Unload the MAPI dll and reset the function pointers to NULL
        FreeLibrary(m_data->m_hMapi);
        m_data->m_hMapi = NULL;
        m_data->m_lpfnMAPILogon = NULL;
        m_data->m_lpfnMAPILogoff = NULL;
        m_data->m_lpfnMAPISendMail = NULL;
        m_data->m_lpfnMAPIResolveName = NULL;
        m_data->m_lpfnMAPIFreeBuffer = NULL;
    }
}

bool wxMapiSession::Logon(const wxString& sProfileName, const wxString& sPassword, wxWindow* pParentWnd)
{
    wxASSERT(MapiInstalled()); //MAPI must be installed
    wxASSERT(m_data->m_lpfnMAPILogon); //Function pointer must be valid

    //Initialise the function return value
    bool bSuccess = false;

    //Just in case we are already logged in
    Logoff();

    //Setup the ascii versions of the profile name and password
    size_t nProfileLength = sProfileName.length();

    char* pszProfileName = NULL;
    char* pszPassword = NULL;
    std::string cbProfile,cbPassword;
    if (nProfileLength)
    {
        cbProfile = sProfileName.mb_str();
        cbPassword = sPassword.mb_str();
        pszProfileName = (char*)cbProfile.c_str();
        pszPassword = (char*)cbPassword.c_str();
    }

    //Setup the flags & UIParam parameters used in the MapiLogon call
    FLAGS flags = 0;
    ULONG nUIParam = 0;
    if (nProfileLength == 0)
    {
        //No profile name given, then we must interactively request a profile name
        if (pParentWnd)
        {
            nUIParam = (ULONG) (HWND) pParentWnd->GetHWND();
            flags |= MAPI_LOGON_UI;
        }
        else
        {
            //No window given, just use the main window of the app as the parent window
            if (wxTheApp->GetTopWindow())
            {
                nUIParam = (ULONG) (HWND) wxTheApp->GetTopWindow()->GetHWND();
                flags |= MAPI_LOGON_UI;
            }
        }
    }

    //First try to acquire a new MAPI session using the supplied settings using the MAPILogon functio
    ULONG nError = m_data->m_lpfnMAPILogon(nUIParam, pszProfileName, pszPassword, flags | MAPI_NEW_SESSION, 0, &m_data->m_hSession);
    if (nError != SUCCESS_SUCCESS && nError != MAPI_E_USER_ABORT)
    {
        //Failed to create a create mapi session, try to acquire a shared mapi session
        wxLogDebug(_("Failed to logon to MAPI using a new session, trying to acquire a shared one\n"));
        nError = m_data->m_lpfnMAPILogon(nUIParam, NULL, NULL, 0, 0, &m_data->m_hSession);
        if (nError == SUCCESS_SUCCESS)
        {
            m_data->m_nLastError = SUCCESS_SUCCESS;
            bSuccess = true;
        }
        else
        {
            wxLogDebug(_("Failed to logon to MAPI using a shared session, Error:%ld\n"), nError);
            m_data->m_nLastError = nError;
        }
    }
    else if (nError == SUCCESS_SUCCESS)
    {
        m_data->m_nLastError = SUCCESS_SUCCESS;
        bSuccess = true;
    }

    return bSuccess;
}

bool wxMapiSession::LoggedOn() const
{
    return (m_data->m_hSession != 0);
}

bool wxMapiSession::MapiInstalled() const
{
    return (m_data->m_hMapi != NULL);
}

bool wxMapiSession::Logoff()
{
    wxASSERT(MapiInstalled()); //MAPI must be installed
    wxASSERT(m_data->m_lpfnMAPILogoff); //Function pointer must be valid

    //Initialise the function return value
    bool bSuccess = false;

    if (m_data->m_hSession)
    {
        //Call the MAPILogoff function
        ULONG nError = m_data->m_lpfnMAPILogoff(m_data->m_hSession, 0, 0, 0);
        if (nError != SUCCESS_SUCCESS)
        {
            wxLogDebug(_("Failed in call to MapiLogoff, Error:%ld"), nError);
            m_data->m_nLastError = nError;
            bSuccess = true;
        }
        else
        {
            m_data->m_nLastError = SUCCESS_SUCCESS;
            bSuccess = true;
        }
        m_data->m_hSession = 0;
    }

    return bSuccess;
}

bool wxMapiSession::Resolve(const std::string& sName, void* lppRecip1)
{
    lpMapiRecipDesc* lppRecip = (lpMapiRecipDesc*) lppRecip1;

    wxASSERT(MapiInstalled()); //MAPI must be installed
    wxASSERT(m_data->m_lpfnMAPIResolveName); //Function pointer must be valid
    wxASSERT(LoggedOn()); //Must be logged on to MAPI
    wxASSERT(m_data->m_hSession); //MAPI session handle must be valid

    //Call the MAPIResolveName function
    char* lpszAsciiName = (char*)sName.c_str();

    ULONG nError = m_data->m_lpfnMAPIResolveName(m_data->m_hSession, 0, lpszAsciiName, 0, 0, lppRecip);
    if (nError != SUCCESS_SUCCESS)
    {
        wxLogDebug(_("Failed to resolve the name: %s, Error:%ld\n"),
            wxString::FromAscii(sName.c_str()).wx_str(), nError);
        m_data->m_nLastError = nError;
    }
    return (nError == SUCCESS_SUCCESS);
}

bool wxMapiSession::Send(const wxMailMessage& message)
{
    wxASSERT(MapiInstalled()); //MAPI must be installed
    wxASSERT(m_data->m_lpfnMAPISendMail); //Function pointer must be valid
    wxASSERT(m_data->m_lpfnMAPIFreeBuffer); //Function pointer must be valid
    wxASSERT(LoggedOn()); //Must be logged on to MAPI
    wxASSERT(m_data->m_hSession); //MAPI session handle must be valid

    std::string sTitle;
    std::string sName1, sName2, sName3;
    std::string sFilename;

    //Initialise the function return value
    bool bSuccess = false;

    //Create the MapiMessage structure to match the message parameter send into us
    MapiMessage mapiMessage;
    ZeroMemory(&mapiMessage, sizeof(mapiMessage));

    std::string cbSubject = message.m_subject.mb_str(), cbBody = message.m_body.mb_str(), cbOriginator;
    mapiMessage.lpszSubject = (char*)cbSubject.c_str();
    mapiMessage.lpszNoteText = (char*)cbBody.c_str();

    mapiMessage.nRecipCount = (ULONG)(message.m_to.GetCount() + message.m_cc.GetCount() + message.m_bcc.GetCount());

    //Allocate the recipients array
    mapiMessage.lpRecips = mapiMessage.nRecipCount ? new MapiRecipDesc[mapiMessage.nRecipCount] : NULL;

    // If we have a 'From' field, use it
    if (!message.m_from.IsEmpty())
    {
        mapiMessage.lpOriginator = new MapiRecipDesc;
        ZeroMemory(mapiMessage.lpOriginator, sizeof(MapiRecipDesc));

        mapiMessage.lpOriginator->ulRecipClass = MAPI_ORIG;
        // TODO Do we have to call Resolve?
        cbOriginator = message.m_from.mb_str();
        mapiMessage.lpOriginator->lpszName = (char*)cbOriginator.c_str();
    }

    //Setup the "To" recipients
    int nRecipIndex = 0;
    size_t nToSize = message.m_to.GetCount();
    size_t i;
    for (i = 0; i < nToSize; i++)
    {
        MapiRecipDesc& recip = mapiMessage.lpRecips[nRecipIndex];
        ZeroMemory(&recip, sizeof(MapiRecipDesc));
        recip.ulRecipClass = MAPI_TO;
        sName1 = message.m_to[i].mb_str();

        //Try to resolve the name
        lpMapiRecipDesc lpTempRecip;
        if (Resolve(sName1, (void*) &lpTempRecip))
        {
            //Resolve worked, put the resolved name back into the sName
            sName1 = lpTempRecip->lpszName;

            //Don't forget to free up the memory MAPI allocated for us
            m_data->m_lpfnMAPIFreeBuffer(lpTempRecip);
        }
        recip.lpszName = (char*)sName1.c_str();
        ++nRecipIndex;
    }

    //Setup the "CC" recipients
    size_t nCCSize = message.m_cc.GetCount();
    for (i = 0; i < nCCSize; i++)
    {
        MapiRecipDesc& recip = mapiMessage.lpRecips[nRecipIndex];
        ZeroMemory(&recip, sizeof(MapiRecipDesc));
        recip.ulRecipClass = MAPI_CC;
        sName2 = message.m_cc[i].mb_str();

        //Try to resolve the name
        lpMapiRecipDesc lpTempRecip;
        if (Resolve(sName2, (void*) &lpTempRecip))
        {
            //Resolve worked, put the resolved name back into the sName
            sName2 = lpTempRecip->lpszName;

            //Don't forget to free up the memory MAPI allocated for us
            m_data->m_lpfnMAPIFreeBuffer(lpTempRecip);
        }
        recip.lpszName = (char*)sName2.c_str();
        ++nRecipIndex;
    }

    //Setup the "BCC" recipients
    size_t nBCCSize = message.m_bcc.GetCount();
    for (i = 0; i < nBCCSize; i++)
    {
        MapiRecipDesc& recip = mapiMessage.lpRecips[nRecipIndex];
        ZeroMemory(&recip, sizeof(MapiRecipDesc));
        recip.ulRecipClass = MAPI_BCC;
        sName3 = message.m_bcc[i].mb_str();

        //Try to resolve the name
        lpMapiRecipDesc lpTempRecip;
        if (Resolve(sName3, (void*) &lpTempRecip))
        {
            //Resolve worked, put the resolved name back into the sName
            sName3 = lpTempRecip->lpszName;

            //Don't forget to free up the memory MAPI allocated for us
            m_data->m_lpfnMAPIFreeBuffer(lpTempRecip);
        }
        recip.lpszName = (char*)sName3.c_str();
        ++nRecipIndex;
    }

    //Setup the attachments
    size_t nAttachmentSize = message.m_attachments.GetCount();
    size_t nTitleSize = message.m_attachmentTitles.GetCount();
    if (nTitleSize)
    {
        wxASSERT(nTitleSize == nAttachmentSize); //If you are going to set the attachment titles then you must set
        //the attachment title for each attachment
    }
    if (nAttachmentSize)
    {
        mapiMessage.nFileCount = (ULONG)nAttachmentSize;
        mapiMessage.lpFiles = new MapiFileDesc[nAttachmentSize];
        for (i = 0; i < nAttachmentSize; i++)
        {
            MapiFileDesc& file = mapiMessage.lpFiles[i];
            ZeroMemory(&file, sizeof(MapiFileDesc));
            file.nPosition = 0xFFFFFFFF;
            sFilename = message.m_attachments[i].mb_str();

            file.lpszPathName = (char*) sFilename.c_str();

            //file.lpszFileName = file.lpszPathName;
            file.lpszFileName = NULL;

            if (nTitleSize && !message.m_attachmentTitles[i].IsEmpty())
            {
                sTitle = message.m_attachmentTitles[i].mb_str();
                file.lpszFileName = (char*)sTitle.c_str();
            }
        }
    }

    //Do the actual send using MAPISendMail
    ULONG nError = m_data->m_lpfnMAPISendMail(m_data->m_hSession, 0, &mapiMessage, MAPI_LOGON_UI|MAPI_DIALOG, 0);
    switch (nError)
    {
        case SUCCESS_SUCCESS:
        case MAPI_USER_ABORT:
            bSuccess = true;
            m_data->m_nLastError = SUCCESS_SUCCESS;
            break;
        default:
            wxLogError(_("Failed to send mail message, Error:%ld\n"), nError);
            m_data->m_nLastError = nError;
            break;
    }

    //Tidy up the Attachements
    if (nAttachmentSize)
        delete [] mapiMessage.lpFiles;
    //Free up the Recipients and Originator memory
    delete [] mapiMessage.lpRecips;
    delete mapiMessage.lpOriginator;
    return bSuccess;
}

long wxMapiSession::GetLastError() const
{
    return m_data->m_nLastError;
}

#endif // __WXMSW__
