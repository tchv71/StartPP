// dbfres.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

class DBFResource
{
public:
    bool Init();

    virtual ~DBFResource();
private:
    wxFFile m_xrcFile;
};
