#include <date.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "list.h"
#include "interface.h"



int main(int argc, char *argv[]) {

    Date d = createDate(1, 2, 2017);

    printf("Dia: %d\n", get_day(d));


    char * path = NULL;


    if (argc > 1) {
        path = strdup(argv[argc - 1]);
    }



    TAD_community tad = init();

    load(tad, path);




    STR_pair aux1;
//    LONG_pair aux2,aux3;
//    LONG_list aux4,aux6,aux7,aux8,aux9,aux11 ;
//    USER aux5;
//    long aux10;


    aux1= info_from_post (tad,801049 );
    //aux2=top_most_active(tad, 10);
    //aux3=pair total_posts(tad, 2016-07-01, 2016-07-31);
    //aux4=questions_with_tag(tad, package-management,2013-03-01, 2013-03-31)
    //aux5=get_user_info(tad, 15811);
    //aux6=most_voted_answers(tad, int 5, 2015-11-01, 2015-11-01);
    //aux7=most_answered_questions(tad, 10, 2015-11-01, 2014-08-11);
    //aux8=contains_word(tad, 'kde', 10);
    //aux9=both_participated(tad, 87, 5691, 10);
    //aux10=better_answer(tad, 30334);
    //aux11=most_used_best_rep(tad, 5, 2013-11-01, 2013-11-30);



    printf("resultado:%s\n %s\n ",  aux1 );
    //printf("resultado:%s\n %s\n ",  get_list(LONG_list aux1, int index);
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //printf("resultado:%s\n %s\n ",
    //parserDoc("Posts.xml");



    return 0;
}