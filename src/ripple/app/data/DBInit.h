//------------------------------------------------------------------------------
/*
    Portions of this file are from Vpallab: https://github.com/vpallabs
    Copyright (c) 2013 - 2014 - Vpallab.com.
    Please visit http://www.vpallab.com/
    
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_DBINIT_H_INCLUDED
#define RIPPLE_DBINIT_H_INCLUDED

namespace ripple {

// VFALCO TODO Tidy these up into a class with functions and return types.
extern const char* RpcDBInit[];
extern const char* TxnDBInit[];
extern const char* LedgerDBInit[];
extern const char* WalletDBInit[];

// VFALCO TODO Figure out what these counts are for
extern int RpcDBCount;
extern int TxnDBCount;
extern int LedgerDBCount;
extern int WalletDBCount;

} // ripple

#endif
