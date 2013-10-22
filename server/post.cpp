#include <stdio.h>
#include <string.h>
#include <iostream>
#include "mongoose.h"
#include "VspdCtoMySQL.h"
static const char *html_form =
  "<html><body>POST example."
  "<form method=\"POST\" action=\"/handle_post_request\">"
  "Input 1: <input type=\"text\" name=\"input_1\" /> <br/>"
  "Input 2: <input type=\"text\" name=\"input_2\" /> <br/>"
  "<input type=\"submit\" />"
  "</form></body></html>";

static int begin_request_handler(struct mg_connection *conn) {
  const struct mg_request_info *ri = mg_get_request_info(conn);
  char post_data[1024], input1[sizeof(post_data)], input2[sizeof(post_data)];
  int post_data_len;

  if (!strcmp(ri->uri, "/index"))
  {
    // User has submitted a form, show submitted data and a variable value
    post_data_len = mg_read(conn, post_data, sizeof(post_data));

    // Parse form data. input1 and input2 are guaranteed to be NUL-terminated
    mg_get_var(post_data, post_data_len, "input_1", input1, sizeof(input1));
    mg_get_var(post_data, post_data_len, "input_2", input2, sizeof(input2));

    // Send reply to the client, showing submitted form values.
    mg_printf(conn, "HTTP/1.0 200 OK\r\n"
              "Content-Type: text/plain\r\n\r\n"
              "Submitted data: [%.*s]\n"
              "Submitted data length: %d bytes\n"
              "input_1: [%s]\n"
              "input_2: [%s]\n",
              post_data_len, post_data, post_data_len, input1, input2);
  }
  //else
  //{
  //  // Show HTML form.
  //  mg_printf(conn, "HTTP/1.0 200 OK\r\n"
  //            "Content-Length: %d\r\n"
  //            "Content-Type: text/html\r\n\r\n%s",
  //            (int) strlen(html_form), html_form);
  //}
  return 1;  // Mark request as processed
}

int main(void) {
  
	std::cout<<"run serve\n";

	char* host="127.0.0.1";
    char* user="root";
    char* port ="3306";
    char* passwd="huyan";
    char* dbname="gamedata"; 
    char* charset = "GBK";//支持中文
    char* Msg = "";//消息变量
    //初始化
    VspdCToMySQL * vspdctomysql = new VspdCToMySQL;
    if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
           std::cout<<("连接成功/r/n");
    else
           std::cout<<(Msg);


   
    //查询
    char * SQL = "SELECT * FROM vcaccesstest";
    string str = vspdctomysql->SelectData(SQL,4,Msg);
    if( str.length() > 0 )
    {
           std::cout<<("查询成功/r/n");
           std::cout<<(str.data());
           std::cout<<("/r/n");
    }
    else
    {
           std::cout<<(Msg);
    }
    //插入
    SQL = "insert into vcaccesstest(ids,username,passwd,address) values(4,'我的','123210','测试地址')";
    if(vspdctomysql->InsertData(SQL,Msg) == 0)
           std::cout<<("插入成功/r/n");
    //更新
    SQL = "update vcaccesstest set username = '修改了',passwd='2345' where ids = 3 ";
    if(vspdctomysql->UpdateData(SQL,Msg) == 0)
           std::cout<<("更新成功/r/n");
    //删除
    SQL = "delete from vcaccesstest where ids = 3 ";
    if(vspdctomysql->DeleteData(SQL,Msg) == 0)
           std::cout<<("删除成功/r/n");
 
    vspdctomysql->CloseMySQLConn();
  struct mg_context *ctx;
  const char *options[] = {"listening_ports", "8080", NULL};
  struct mg_callbacks callbacks;

  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.begin_request = begin_request_handler;
  ctx = mg_start(&callbacks, NULL, options);
  getchar();  // Wait until user hits "enter"
  mg_stop(ctx);

  return 0;
}
