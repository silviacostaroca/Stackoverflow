//
// Created by Silvia Acosta on 23/4/18.
//
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#ifndef GRUPO3_PARSER_H
#define GRUPO3_PARSER_H



TAD_community parserDoc(TAD_community com, char *filename);

TAD_community parsePost(xmlNodePtr cur, TAD_community com);
TAD_community parseUser(xmlNodePtr cur, TAD_community com);
TAD_community parseVote(xmlNodePtr cur, TAD_community com);


#endif //GRUPO3_PARSER_H