//
// Created by Silvia Acosta on 11/4/18.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "interface.h"
#include "parser.h"



#define MAX 100
#define FALSE -1
#define TRUE 0
#define QUESTION 1
#define ANSWER 2


typedef struct User {
    int id;
    char *nome;
    int nPosts;
    int Reputation;
    char *AboutMe;
};

typedef struct Post {
    int id;
    char *titulo;
    int ownerUserId;
    int postTypeId;
    int parentID;
    char *creationDate;
    char *tag;
    int answerCount;
    int commentCount;
    int score;
};


typedef struct Vote {
    int voteTypeId;
    int postId;
};


struct TCD_community {
    struct Post **posts;
    int maxPosts;
    int nPosts;


    struct User **users;
    int maxUsers;
    int nUsers;

    struct Vote **votes;
    int maxVotes;
    int nVotes;

}sTCD_community;


TAD_community init() {
    TAD_community com = (TAD_community) malloc(sizeof(struct TCD_community));
    com->maxPosts = MAX;
    com->maxUsers = MAX;
    com->maxVotes = MAX;
    com->nPosts = 0;
    com->nUsers = 0;
    com->nVotes = 0;
    com->posts = NULL;
    com->users = NULL;
    com->votes = NULL;

    return com;
}

// query 0
char *criaPath(char *dump_path, char *fileName) {
    char *caminho = (char *) malloc(100 * sizeof(char));
    sprintf(caminho, "%s/%s", dump_path, fileName);
    return caminho;
}

TAD_community load(TAD_community com, char *dump_path) {
    char *pathubPost = strdup("ubuntu/Posts.xml");
    char *pathandPost = strdup("android/Posts.xml");
    char *pathubUser = strdup("ubuntu/Users.xml");
    char *pathandUser = strdup("android/Users.xml");
    char *pathubVote = strdup("ubuntu/Votes.xml");
    char *pathandVote = strdup("android/Votes.xml");



    if (dump_path != NULL) {
        pathubPost = criaPath(dump_path, pathubPost);
        pathandPost = criaPath(dump_path, pathandPost);
        pathubUser = criaPath(dump_path, pathubUser);
        pathandUser = criaPath(dump_path, pathandUser);
        pathubVote = criaPath(dump_path, pathubVote);
        pathandVote = criaPath(dump_path, pathandVote);
    }


    //Invoca a função de parser onde é passado o caminho do ficheiro que queremos fazer o parser
    com = parserDoc(com, pathubPost);
    com = parserDoc(com, pathandPost);
    com = parserDoc(com, pathubUser);
    com = parserDoc(com, pathandUser);
    com = parserDoc(com, pathubVote);
    com = parserDoc(com, pathandVote);

    //Devolve (apontador para) estrutura já com os dados resultantes do parser


    //printf("nPosts: %d\n", com->posts[0]->id);
    //printf("nUsers: %d\n", com->users[0]->id);
    //printf("nVotes: %d\n", com->votes[0]->id);

    return com;
}





////////////////////////////////////////////////////////////////////////




int numPostusuario(TAD_community com, int id) {
    int nPosts = 0;

    for (int i = 0; i < (com->nPosts); i++) {
        if ((com->posts[i])->ownerUserId == id)
            nPosts++;
    }
    return nPosts;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 1.- Dado o identificador de um post, a fuņc̃ao deve retornar o t́ıtulo do post e o nome (na ̃o o ID) de utilizador
 do autor.
 Se o post for uma resposta, a fuņca ̃o dever ́a retornar informa̧cões (t́ıtulo e utilizador) da pergunta correspondente*/

STR_pair info_from_post(TAD_community com, long id) {
    STR_pair *resposta = NULL;
    struct Post **posts = com->posts;
    for (int i = 0; i < (com->nPosts); i++) {
        if ((com->posts[i])->id == id)
            resposta = create_str_pair(posts[i]->titulo, com->users[posts[i]->ownerUserId]->nome);
    }
    return resposta;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*2.- Pretende obter o top N utilizadores com maior número de posts de sempre.
Para isto, devem ser considerados tanto perguntas quanto respostas dadas pelo respectivo utilizador
LONG_list top_most_active(TAD_community com, int N) {
    LONG_list *listposts = create_list(com->nUsers);
    LONG_list *listusers = create_list(com->nUsers);
    for (int i = 0; i < (com->nUsers); i++) {
        set_list(listposts, i, (long) (com->users[i]->nPosts));
        set_list(listusers, i, (long) (com->users[i]->id));
    }
    void ordenaListas(LONG_list *listusers,
                      LONG_list *listposts); // TODO: Ordenar as listas e devolver um  lista nova com os N 1ºs.
    LONG_list *resultado = create_list(N);
    for (int i = 0; i < N; i++) {
        set_list(resultado, i, get_list(listusers, i));
    }
    resultado;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*3.- Dado um intervalo de tempo arbitrário, obter o número total de posts(identificando perguntas e respostas
 separadamente) neste peŕıodo;*/

LONG_pair total_posts(TAD_community com, Date begin, Date end) {
    struct Post **posts = com->posts;
    LONG_pair *resposta = NULL;
    long q1 = 0;
    long q2 = 0;

    for (int i = 0; i < (com->nPosts); i++) {
        if (strcmp(posts[i]->creationDate, end) <= 0 && strcmp(posts[i]->creationDate, begin) >= 0) {
            if (posts[i]->postTypeId == 1) q1++;
            else q2++;
        }
        resposta = create_long_pair(q1, q2);
    }
    return resposta;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*4.- Dado um intervalo de tempo arbitŕario, retornar todas as perguntas contendo uma determinada tag. O retorno da
fuņcão deveŕa ser uma lista com os IDs das perguntas ordenadas em cronologia inversa;*/

LONG_list questions_with_tag(TAD_community com, char *tag, Date begin, Date end) {

    struct Post **posts = com->posts;
    LONG_list *resposta = create_list(com->nPosts);
    int c = 0;

    for (int i = 0; i < (com->nPosts); i++) {
        if (strcmp(posts[i]->creationDate, end) <= 0 && strcmp(posts[i]->creationDate, begin) >= 0) {
            if ((posts[i]->postTypeId == 1) && (strcmp(posts[i]->tag, tag))) {
                set_list(resposta, c, posts[i]->id);
                c++;

            }
        }
    }
    return resposta;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*5.- Dado um ID de utilizador, devolver a informa̧cão do seu perfil (short bio) e os IDs dos seus 10 ultimos posts
(perguntas ou respostas), ordenados por cronologia inversa;*/



USER get_user_info(TAD_community com, long id) {
    struct User *resposta = NULL;

    for (int i = 0; i < (com->nUsers); i++) {

        if ((com->users[i])->id == id)
            resposta = create_user(get_bio(id), get_10_latest_posts(id));

    }
    return resposta;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*6.- Dado um intervalo de tempo arbitŕario, devolver os IDs das N respostas com mais votos, em ordem decrescente do
número de votos; O número de votos devera ser obtido pela difereņca entre Up Votes (UpMod) e Down Votes
(DownMod).
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
7.- Dado um intervalo de tempo arbitŕario, devolver as IDs das N perguntas com mais respostas, em ordem decrescente
 do número de respostas;
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
8.- Dado uma palavra, devolver uma lista com os IDs de N perguntas cujos t́ıtulos a contenham, ordenados por cronologia
inversa;
LONG_list contains_word(TAD_community com, char* word, int N);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
9.- Dados os IDs de dois utilizadores, devolver as últimas N perguntas (cronologia inversa) em que participaram dois
utilizadores espećıficos. Note que os utilizadores podem ter participado via pergunta ou respostas;
LONG_list both_participated(TAD_community com, long id1, long id2, int N);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*10.- Dado o ID de uma pergunta, obter a melhor resposta. Para isso, dever ́a usar a funç̃ao de ḿedia ponderada abaixo:
(Scr × 0.45) + (Rep × 0.25) + (V ot × 0.2) + (Comt × 0.1)
• Scr - score da resposta;
• Rep - reputa̧cão do utilizador;
• Vot - nu ́mero de votos recebidos pela resposta;
• Comt - número de comentários recebidos pela resposta
int numeroUpDown (TAD_community com, int id){
    struct Vote **votes = com->votes;
    int up=0;
    int down=0;
    int rtdo=0;
    for (int i=0; i<com->nVotes; i++){
        if ((votes[i]->postId) == id){
            if((votes[i]->voteTypeId)==2)
                up++;
            if((votes[i]->voteTypeId)==3)
                down++;
        }
    }
    rtdo=up-down;
    return rtdo;
}
long better_answer(TAD_community com, long id) {
    struct Post **posts = com->posts;
    struct User **users = com->users;
    struct Vote **votes = com->votes;
    long Scr = 0;
    long Rep = 0;
    long Vot = 0;
    long Comt = 0;
    long r = 0;
    long max = 0;
    for (int i = 0; i < (com->nPosts); i++) {
        if ((posts[i]->postTypeId == 2) && (posts[i]->parentID==id)) {
            Scr = posts[i]->score;
            for (int j = 0; j < (com->nUsers); j++) {
                if (users[j]->id == posts[i]->ownerUserId)
                    Rep = (users[j]->Reputation);
            }
            for (int k = 0; k < (com->nVotes); k++){
                if (votes[k]->postId == posts[i]->id)
                    Vot=numeroUpDown (com, id);
                }
            Comt = posts[i]->commentCount;
        }
        r = (Scr * 0.45) + (Rep * 0.25) + (Vot * 0.2) + (Comt * 0.1);
        if (r > max)
            max = r;
    }
    return max;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Dado um intervalo arbitrário de tempo, devolver os identificadores das N tags mais usadas pelos N utilizadores com
melhor reputa̧cão. Em ordem decrescente do nu ́mero de vezes em que a tag foi usada.
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);*/





/////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////PARSER//////////////////////////////////


TAD_community reallocPosts(TAD_community com) {
    int i = 0;

    struct Post **auxPosts = (struct Post *) malloc(2 * (com->maxPosts) * sizeof(struct Post));

    for (i = 0; i < com->nPosts; i++) {
        auxPosts[i] = com->posts[i];
    }

    struct Post **aux = com->posts;
    com->posts = auxPosts;

    free(aux);

    com->maxPosts = 2 * com->maxPosts;

    return com;
}


TAD_community insertPost(TAD_community com, int id, char *titulo, int ownerUserId, int postTypeId, int parentID,
                         char *creationDate,char *tag, int answerCount, int commentCount, int score) {
    if (com->nPosts >= com->maxPosts) {
        com = reallocPosts(com);
    }
    com->posts[com->nPosts] = (struct Post *) malloc(MAX * sizeof(struct Post));
    com->posts[com->nPosts]->id = id;
    com->posts[com->nPosts]->titulo = strdup(titulo);
    com->posts[com->nPosts]->ownerUserId = ownerUserId;
    com->posts[com->nPosts]->postTypeId = postTypeId;
    com->posts[com->nPosts]->parentID = parentID;
    com->posts[com->nPosts]->creationDate = strdup(creationDate);
    com->posts[com->nPosts]->tag = strdup(tag);
    com->posts[com->nPosts]->answerCount = answerCount;
    com->posts[com->nPosts]->commentCount = commentCount;
    com->posts[com->nPosts]->score = score;
    com->nPosts++;

    return com;
}


TAD_community reallocUsers(TAD_community com) {
    int i = 0;

    struct User **auxUsers = (struct User *) malloc(2 * com->maxUsers * sizeof(struct User));

    for (i = 0; i < com->nUsers; i++) {
        auxUsers[i] = com->users[i];
    }

    struct Users *aux = com->users;
    com->users = auxUsers;

    free(aux);

    com->maxUsers = 2 * com->maxUsers;

    return com;
}


TAD_community insertUser(TAD_community com, int id, char *nome, int nPosts, int Reputation, char *AboutMe, int upMod, int downMod) {

    if (com->nUsers >= com->maxUsers) {
        com = reallocUsers(com);
    }
    com->users[com->nUsers] = (struct User *) malloc(MAX * sizeof(struct User));
    com->users[com->nUsers]->id = id;
    com->users[com->nUsers]->nome = strdup(nome);
    com->users[com->nUsers]->nPosts = numPostusuario(com, id);
    com->users[com->nUsers]->Reputation = Reputation;
    com->users[com->nUsers]->AboutMe = strdup(AboutMe);
    com->nUsers++;

    return com;
}




TAD_community reallocVotes(TAD_community com) {
    int i = 0;

    struct Vote **auxVotes = (struct Vote *) malloc(2 * com->maxVotes * sizeof(struct Vote));

    for (i = 0; i < com->nVotes; i++) {
        auxVotes[i] = com->votes[i];
    }

    struct Votes *aux = com->votes;
    com->votes = auxVotes;

    free(aux);

    com->maxVotes = 2 * com->maxVotes;

    return com;
}


TAD_community insertVote(TAD_community com, int voteTypeId, int postId) {

    if (com->nVotes >= com->maxVotes) {
        com = reallocVotes(com);
    }
    com->votes[com->nVotes] = (struct Vote *) malloc(MAX * sizeof(struct Vote));
    com->votes[com->nVotes]->postId = postId;
    com->votes[com->nVotes]->voteTypeId = voteTypeId;
    com->nVotes++;

    return com;
}







int cleanPosts(struct Post *p) {
    free(p->titulo);
    free(p->creationDate);
    free(p->tag);
    free(p);
    p = NULL;

    return TRUE;
}

int cleanUsers(struct User *u) {
    free(u->nome);
    free(u->AboutMe);
    free(u);
    u = NULL;

    return TRUE;
}

int cleanVotes(struct Vote *v) {
    free(v);
    v  = NULL;

    return TRUE;
}



TAD_community clean(TAD_community com) {
    int i = 0;

    for (i = 0; i < com->nPosts; i++) {
        cleanPosts(com->posts[i]);
    }

    for (i = 0; i < com->nUsers; i++) {
        cleanUsers(com->users[i]);
    }

    for (i = 0; i < com->nVotes; i++) {
        cleanVotes(com->votes[i]);
    }
    free(com);
    com = NULL;

    return com;
}



