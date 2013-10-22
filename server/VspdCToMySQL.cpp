#include "VspdCToMySQL.h"
VspdCToMySQL::VspdCToMySQL()
{
}
 
VspdCToMySQL::~VspdCToMySQL()
{
}
 
//��ʼ������
int VspdCToMySQL::ConnMySQL(char *host,char * port ,char * Db,char * user,char* passwd,char * charset,char * Msg)
{
       if( mysql_init(&mysql) == NULL )
       {
              Msg = "inital mysql handle error";
              return 1;
       }    
 
       if (mysql_real_connect(&mysql,host,user,passwd,Db,0,NULL,0) == NULL)
       {
              Msg = "Failed to connect to database: Error";
              return 1;
       }    
 
       if(mysql_set_character_set(&mysql,"GBK") != 0)
       {
              Msg = "mysql_set_character_set Error";
              return 1;
       }
       return 0;
}
 
//��ѯ����
string VspdCToMySQL::SelectData(char * SQL,int Cnum,char * Msg)
{
       MYSQL_ROW m_row;
    MYSQL_RES *m_res;
    char sql[2048];
    sprintf(sql,SQL);
       int rnum = 0;
       char rg = 0x06;//�и���
       char cg = {0x05};//�ֶθ���
 
       if(mysql_query(&mysql,sql) != 0)
       {
              Msg = "select ps_info Error";
              return "";
       }
       m_res = mysql_store_result(&mysql);
 
       if(m_res==NULL)
       {
              Msg = "select username Error";
              return "";
       }
       string str("");
       while(m_row = mysql_fetch_row(m_res))
       {
              for(int i = 0;i < Cnum;i++)
              {
                     str += m_row[i];
                     str += rg;
              }
              str += rg;             
              rnum++;
       }
 
       mysql_free_result(m_res);
 
       return str;
}
 
//��������
int VspdCToMySQL::InsertData(char * SQL,char * Msg)
{
       char sql[2048];
    sprintf(sql,SQL);
       if(mysql_query(&mysql,sql) != 0)
       {
              Msg = "Insert Data Error";
              return 1;
       }
       return 0;
}
 
//��������
int VspdCToMySQL::UpdateData(char * SQL,char * Msg)
{
       char sql[2048];
    sprintf(sql,SQL);
       if(mysql_query(&mysql,sql) != 0)
       {
              Msg = "Update Data Error";
              return 1;
       }
       return 0;
}
 
//ɾ������
int VspdCToMySQL::DeleteData(char * SQL,char * Msg)
{
       char sql[2048];
    sprintf(sql,SQL);
       if(mysql_query(&mysql,sql) != 0)
       {
              Msg = "Delete Data error";
              return 1;
       }
       return 0;
}
 
//�ر����ݿ�����
void VspdCToMySQL::CloseMySQLConn()
{
       mysql_close(&mysql);
}
 
// 
//6�� ��main��������������������̼�����main�ˣ�������һ����ť����Ĵ���飩���      һЩ���룬���֮�����£�
//#include "stdafx.h"
//#include "VspdCTOMySQL.h"
// 
//int main(int argc, char* argv[])
//{
//    char* host="MYSQL������IP";
//    char* user="root";
//    char* port ="3306";
//    char* passwd="�û�����";
//    char* dbname="���ݿ�����"; 
//    char* charset = "GBK";//֧������
//    char* Msg = "";//��Ϣ����
//    //��ʼ��
//    VspdCToMySQL * vspdctomysql = new VspdCToMySQL;
//    if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
//           printf("���ӳɹ�/r/n");
//    else
//           printf(Msg);
//   
//    //��ѯ
//    char * SQL = "SELECT ids,username,passwd,address FROM vcaccesstest";
//    string str = vspdctomysql->SelectData(SQL,4,Msg);
//    if( str.length() > 0 )
//    {
//           printf("��ѯ�ɹ�/r/n");
//           printf(str.data());
//           printf("/r/n");
//    }
//    else
//    {
//           printf(Msg);
//    }
//    //����
//    SQL = "insert into vcaccesstest(ids,username,passwd,address) values(4,'�ҵ�','123210','���Ե�ַ')";
//    if(vspdctomysql->InsertData(SQL,Msg) == 0)
//           printf("����ɹ�/r/n");
//    //����
//    SQL = "update vcaccesstest set username = '�޸���',passwd='2345' where ids = 3 ";
//    if(vspdctomysql->UpdateData(SQL,Msg) == 0)
//           printf("���³ɹ�/r/n");
//    //ɾ��
//    SQL = "delete from vcaccesstest where ids = 3 ";
//    if(vspdctomysql->DeleteData(SQL,Msg) == 0)
//           printf("ɾ���ɹ�/r/n");
// 
//    vspdctomysql->CloseMySQLConn();
// 
//    return 0;
//}