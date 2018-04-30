#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "parser.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>


#define QUESTION 1
#define ANSWER 2


//typedef struct TCD_community *TAD_community;


TAD_community parserDoc(TAD_community com, char *filename) {
    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(filename);//apontador para o meu ficheiro

    /* Vai buscar o apontador para o ficheiro
     * Se o apontador para o ficheiro está a NULL (não consegui abrir o ficheiro, ou não existe ficheiro para abrir)*/
    if (doc == NULL) {
        fprintf(stderr, "Document not parsed.\n");
        return NULL;
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        fprintf(stderr, "Empty document\n");
        xmlFreeDoc(doc);
        return NULL;
    }

    cur = cur->xmlChildrenNode;

    //Se em cur temos um post, chamamos a função que trata do parser do ficheiro posts
    if ((!xmlStrcmp(cur->name, (const xmlChar *) "posts"))) {
        com = parsePost(cur, com);
    }

    //Se em cur temos um user, chamamos a função que trata do parser do ficheiro users
    if ((!xmlStrcmp(cur->name, (const xmlChar *) "users"))) {
        com = parseUser(cur, com);
    }
    //Se em cur temos um vote, chamamos a função que trata do parser do ficheiro votes
    if ((!xmlStrcmp(cur->name, (const xmlChar *) "votes"))) {
        com = parseVote(cur, com);
    }
    xmlFreeDoc(doc);

    return com;
}


/////////////////////////////////////////////////// POSTS //////////////////////////////////////////////////////////////////////////////////////////////////


TAD_community parsePost(xmlNodePtr cur, TAD_community com) {
    printf("DDDD 1 Parse Post"); // TODO: REMOVER
    struct Post *post = NULL;
    xmlChar *id; //Id
    xmlChar *titulo; //Title
    xmlChar *ownerUserId; //OwnerUserId
    xmlChar *postTypeId; //PostTypeId
    xmlChar *parentID; //ParentId -> Os posts têm todos parentID?
    xmlChar *creationDate; //CreationDate
    xmlChar *tag; //Tags
    xmlChar *answerCount; //AnswerCount
    xmlChar *commentCount; //CommentCount
    xmlChar *score; //Score


    cur = cur->xmlChildrenNode; //APonta para o primeiro nodo row

    while (cur != NULL) { //Vamos percorrer todos os nodos do ficheiro

        if ((!xmlStrcmp(cur->name, (const xmlChar *) "row"))) { //Estamos no nodo
            id = xmlGetProp(cur, "Id");
            titulo = xmlGetProp(cur, "Title");
            ownerUserId = xmlGetProp(cur, "OwnerUserId");
            postTypeId = xmlGetProp(cur, "PostTypeId");
            parentID = (postTypeId == ANSWER) ? xmlGetProp(cur, "ParentId") : NULL;
            creationDate = xmlGetProp(cur, "CreationDate");
            tag = xmlGetProp(cur, "Tags");
            answerCount = xmlGetProp(cur, "AnswerCount");
            commentCount = xmlGetProp(cur, "CommentCount");
            score = xmlGetProp(cur, "Score");

            post = insertPost(atoi((char *) id), (char *) titulo, atoi((char *) ownerUserId), atoi((char *) postTypeId),
                              atoi((char *) parentID), (char *) creationDate, (char *) tag, atoi((char *) answerCount),
                              atoi((char *) commentCount), atoi((char *) score));
        }
        cur = cur->next;

    }

    return com;

}



/////////////////////////////////////////////////// USER //////////////////////////////////////////////////////////////////////////////////////////////////


TAD_community parseUser(xmlNodePtr cur, TAD_community com) {
    printf("DDDD 1 Parse User"); // TODO: REMOVER

    struct User *user = NULL;
    xmlChar *id; //Id
    xmlChar *nome; //DisplayName
    int nPosts; //
    xmlChar *reputation; //Reputation
    xmlChar *aboutMe; //AboutMe

    cur = cur->xmlChildrenNode;

    while (cur != NULL) { //Vamos percorrer todos os nodos do ficheiro

        if ((!xmlStrcmp(cur->name, (const xmlChar *) "row"))) { //Estamos no nodo
            id = xmlGetProp(cur, "Id");

            printf("DDDD %s", (char *) id); // TODO: REMOVER

            nome = xmlGetProp(cur, "DisplayName");
            reputation = xmlGetProp(cur, "Reputation");
            aboutMe = xmlGetProp(cur, "AboutMe");

            nPosts = 0;
            user = insertUser(atoi((char *) id), (char *) nome, nPosts, atoi((char *) reputation),
                              (char *) aboutMe);
        }
        cur = cur->next;

    }

    return com;
}


/////////////////////////////////////////////////// VOTES //////////////////////////////////////////////////////////////////////////////////////////////////



TAD_community parseVote(xmlNodePtr cur, TAD_community com) {
    struct Vote *vote = NULL;
    xmlChar *idPost; //PostId
    xmlChar *voteTypeId; //VoteTypeId

    cur = cur->xmlChildrenNode;

    while (cur != NULL) { //Vamos percorrer todos os nodos do ficheiro

        if ((!xmlStrcmp(cur->name, (const xmlChar *) "row"))) { //Estamos no nodo
            idPost = xmlGetProp(cur, "PostId");

            voteTypeId = xmlGetProp(cur, "VoteTypeId");


            vote = insertVote(atoi((char *) idPost), atoi((char *) voteTypeId));
        }
        cur = cur->next;

    }

    return com;
}
