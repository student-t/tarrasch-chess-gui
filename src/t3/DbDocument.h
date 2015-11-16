/****************************************************************************
 * A Game in a GameCache - From the database
 *  Author:  Bill Forster
 *  License: MIT license. Full text of license is in associated file LICENSE
 *  Copyright 2010-2015, Bill Forster <billforsternz at gmail dot com>
 ****************************************************************************/
#ifndef DB_DOCUMENT_H
#define DB_DOCUMENT_H
#include "GameDocument.h"
#include "CompactGame.h"
#include "PackedGame.h"
#include "CompressMoves.h"

class DbDocument : public MagicBase
{
private:
    int game_id;
    PackedGame pack;

public:
    DbDocument( int game_id, Roster &r, std::string str_blob )
    {
        this->game_id = game_id;
        pack.Pack( r, str_blob );
    }

    virtual int GetGameId()  { return game_id; }

    virtual void GetCompactGame( CompactGame &pact )
    {
        pack.Unpack(pact);
    }
    
	virtual GameDocument  *GetGameDocumentPtr()
    {
        static GameDocument  the_game;
        CompactGame pact;
        GetCompactGame( pact );
        pact.Upscale(the_game);
        return &the_game;
    }

    virtual bool HaveStartPosition() { return false; }
    
    virtual Roster &RefRoster()
    {
        static Roster r;
        pack.Unpack(r);
        return r;
    }
    virtual std::vector<thc::Move> &RefMoves()
    {
        static CompactGame pact;
        GetCompactGame( pact );
        return pact.moves;
    }
    virtual std::string &RefCompressedMoves()
    {
        static std::string blob;
        blob.clear();
        pack.Unpack(blob);
        return blob;
    }
    virtual thc::ChessPosition &RefStartPosition()
    {
        static CompactGame pact;
        GetCompactGame( pact );
        return pact.start_position;
    }
    
    
};


#endif    // DB_DOCUMENT_H