//
//  JSONTest.c
//  MembraneAutomata
//
//  Created by Mitsuyoshi Yamazaki on 4/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "JSONTest.h"
#include "json.h"
#include "MMADefinition.h"
#include <string.h>
#include <stdlib.h>

void fileTest() {
	FILE *outputfile;         // 出力ストリーム
	
	char filename[] = "file_writing_test4";
	
	outputfile = fopen(filename, "w");  // ファイルを書き込み用にオープン(開く)
	if (outputfile == NULL) {          // オープンに失敗した場合
		printf("cannot open\n");         // エラーメッセージを出して
		return;
	}
	
	
	int filesize = 0x0f;
	unsigned char *context = (unsigned char*)malloc(sizeof(const char) * filesize);

	for (int i = 0; i < filesize; i++) {
		context[i] =i;
	}
	
	fwrite(context, sizeof(unsigned char), 0x0f, outputfile);
//	fprintf(outputfile, context); // ファイルに書く

	fclose(outputfile);          // ファイルをクローズ(閉じる)

	printf("\n\nhogehoge\n\n");
	
	//
	FILE *fp;
//	char *fname = "test.bmp";
	unsigned char buf[10000];
	int  i, size;
	
	fp = fopen( filename, "rb" );
	if( fp == NULL ){
		printf( "%sファイルが開けません¥n", filename);
		return;
	}
	
	size = fread( buf, sizeof( unsigned char ), 0x0b, fp );
	
	for( i=0; i<size; i++ ){
//		if( i % 16 == 0 ) printf( "¥n" );
		printf( "%02X ", buf[i] );
	}
	
	fclose( fp );

	
	unsigned int pake = 0 - 1;
	printf("\n pake : %d", pake);
	
	char hogehoge[100];
	sprintf(hogehoge, "[this is hoge %d, %x, %s]", 3244, 0xb2, "foo");
	printf("hogehoge : {%s}", hogehoge);
}

void jsonTest() {
	/*
	char buff0[256];   // 連結文字列用 
	
	for (int i = 0; i < 256; i++) {
		buff0[i] = 0x00;
	}
	
    char buff1[] = "{'hoge':'";   // 入力文字列用
    char buff2[] = "'}";   // 入力文字列用 
	
    printf("文字列1 : %s\n", buff1);  // プロンプト表示 
    printf("文字列2 : %s\n", buff2);  // プロンプト表示 
	
	char hoge[8] = {0x03,0x02,0x04,0x04,0x04,0x06,0x04,0x09};	
	
	
	
    strcpy(buff0, buff1);  // 文字列コピー(buff$ = buff1$) 
    strcat(buff0, hoge);  // 文字列連結(buff$ = buff$ + buff2$) 
//	strcat(buff0, buff2);
	
    printf("文字列は%sです\n", buff0);    // 連結文字列表示 
*/
	
	struct json_object *obj, *obj2;
	char buff[] = "{'a':1,'b':2,'c':3,'d':'hoge','foo':'3244'}";
    obj = json_tokener_parse(buff);
	
	obj2 = json_tokener_parse("32");
	
	json_object_object_add(obj, "pakerattaKey", obj2);
	
    json_object_object_foreach(obj, key, val) {
        printf("\t%s: %s\n", key, json_object_to_json_string(val));
    }


	
	/*
	char file[] = "pattern_json_test";
	
	MMAPattern pattern;
	MMAPatternInitialize(&pattern, MMASizeMake(10, 10), MMARuleRuleSet, 4);
	
//	storePattern(&pattern, file);

	struct json_object *obj;
    int i;
    obj = json_tokener_parse("{'a':1,'b':2,'c':3,'d':'hoge','foo':'3244'}");
	
	char hogera[] = "3";
	struct json_object *obj2 = json_tokener_parse(hogera);

	json_object_object_add(obj, "pake", obj2);
    json_object_object_foreach(obj, key, val) {
        printf("\t%s: %s\n", key, json_object_to_json_string(val));
    }
*/
	
	/*
	struct json_object *obj;
    int i;
	
    obj = json_tokener_parse("[1,2,3]");
    for(i=0; i < json_object_array_length(obj); i++) {
        struct json_object *a = json_object_array_get_idx(obj, i);
        printf("\t[%d]=%s\n", i, json_object_to_json_string(a));
    }
//	int hoge = 3244;
    obj = json_tokener_parse("{'a':1,'b':2,'c':3,'d':'hoge','foo':'3244'}");
    json_object_object_foreach(obj, key, val) {
        printf("\t%s: %s\n", key, json_object_to_json_string(val));
    }
	
	char buf[] = "{\"SERVER\":{\"host\": \"192.168.0.2\", \"port\":1287},\"CLIENT\":[[\"192.168.0.3\",1001,\"CLIENT1\"],[\"192.168.0.4\",1002,\"CLIENT2\"]]}";
	obj = json_tokener_parse(buf);
	json_object_object_foreach(obj, key1, val1) {
        printf("\t%s: %s\n", key1, json_object_to_json_string(val1));
    }

	printf("\n");
	char hoge[] = "{'c':[10,20,30],'d':[[1,2],[3,4]]}";
	obj = json_tokener_parse(hoge);
	json_object_object_foreach(obj, key2, val2) {
        printf("\t%s: %s\n", key2, json_object_to_json_string(val2));
//		json_object_object_foreach(val2, key00, val00) {
//			printf("\t\t%s: %s\n", key00, json_object_to_json_string(val00));
//		}
    }
	*/
	
		
	/*
	char fileName[] = "jsontestfile2";
	int succeeded = 0;//json_object_to_file(fileName, obj);
	
	if (succeeded == -1) {
		printf("file create failed\n");
	}
	else if (succeeded == 0) {
		printf("file create succeeded\n");
	}
	else {
		printf("( -.-)?\n");
	}
	
	obj = json_tokener_parse(hoge);	
	char filename2[] = "hoge";
//	json_object_to_file(filename2, obj);
	

	printf("\nfrom file\n");
	struct json_object *newObj;
	newObj = json_object_from_file(fileName);
	json_object_object_foreach(newObj, key3, val3) {
        printf("\t%s: %s\n", key3, json_object_to_json_string(val3));
    }

	printf("\nfrom file\n");
	struct json_object *newObj2;
	newObj2 = json_object_from_file(filename2);
	json_object_object_foreach(newObj2, key4, val4) {
        printf("\t%s: %s\n", key4, json_object_to_json_string(val4));
    }
*/
	/*
	struct json_object *obj;
	struct json_object *srv, *cli;
	int i;
	char buf[] = "{\"SERVER\":{\"host\": \"192.168.0.2\", \"port\":1287},\"CLIENT\":[[\"192.168.0.3\",1001,\"CLIENT1\"],[\"192.168.0.4\",1002,\"CLIENT2\"]]}";
	int len;
	mc_set_debug(1);
	obj = json_tokener_parse(buf);
	printf("new_obj.to_string()=%s\n", json_object_to_json_string(obj));
	srv =json_object_object_get(obj, "SERVER");
	cli =json_object_object_get(obj, "CLIENT");
	printf("srv.to_string()=%s\n", json_object_to_json_string(srv));
	printf("cli.to_string()=%s\n", json_object_to_json_string(cli));
	json_object_object_foreach(srv, key,val)
	{
		printf("\t%s: %s\n",key,json_object_to_json_string(val));
	}
	len = json_object_array_length(cli);
	printf("cli.length: %d\n",len);
	struct json_object *ary;
	struct array_list *ary_list;
	for (i = 0; i &lt; len; i++)
	{
		ary = json_object_array_get_idx(cli, i);
		printf(&quot;ary.to_string()=%s\n&quot;, json_object_to_json_string(ary));
		char *str;
		int ary_len;
		ary_list = json_object_get_array(ary);
		ary_len = array_list_length(ary_list);
		printf(&quot;ary_length: %d\n&quot;,ary_len);
		char *ipaddr;
		ipaddr = json_object_get_string((struct json_object *)array_list_get_idx(ary_list,0));
		printf(&quot;ipaddr: %s\n&quot;,ipaddr);
		int portno;
		portno = json_object_get_int((struct json_object *)array_list_get_idx(ary_list,1));
		printf(&quot;portno: %d\n&quot;,portno);
		char *pcname;
		pcname = json_object_get_string((struct json_object *)array_list_get_idx(ary_list,2));
		printf(&quot;pcname: %s\n&quot;,pcname);
	}
	return (EXIT_SUCCESS);
	*/
}