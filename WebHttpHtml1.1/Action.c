Action()
{
	int elemCnt;
	
	int x;
	
	char arrayParamName[50]; 
		
	
	lr_start_transaction("����� ������ ������������� ���������");

		web_reg_find("Text=��������", 
			LAST);
		
		//��������� id ���� ������������� ���������
		
		web_reg_save_param_ex("ParamName=MESSAGE_ID", 
	        "NOTFOUND=WARNING", 	//�� ������, ���� ��� ������������� ���������
		    "LB/IC=\<span class=\"b-messages__message__left\" href=\"\/lite\/message\/",
			"RB/IC=\/new\"\>",
			"Ordinal=all",
			SEARCH_FILTERS,
		  	"Scope=body", 
		  	LAST);
		
		web_url("unread", 
			"URL=https://mail.yandex.ru/lite/unread", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t219.inf", 
			"Mode=HTML", 
			LAST);
		
		elemCnt = atoi(lr_eval_string("{MESSAGE_ID_count}"));

		lr_output_message("����� ������������� ��������� = %d", elemCnt);
		
	lr_end_transaction("����� ������ ������������� ���������", LR_AUTO);
	
	
	lr_start_transaction("�������� ������������� ��������� � �����");
	
		for (x = 1; x <= elemCnt; x++) {
		
		    sprintf(arrayParamName, "{MESSAGE_ID_%d}", x);
		    
		    lr_save_string(lr_eval_string(arrayParamName), "id");
		
		 	//���������� ������
		    
		    lr_output_message ("%s: %s",
		        arrayParamName,
		        lr_eval_string(arrayParamName)); 
		      
		    
		    //�������� ������
		
			web_reg_find("Text=��������", 
				LAST);
		
			web_url("{id}/new", 
				"URL=https://mail.yandex.ru/lite/message/{id}/new", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Snapshot=t220.inf", 
				"Mode=HTML", 
				LAST);
		
		    
			//������� �� ��������
			
			web_reg_find("Text=��������", 
				LAST);
		
			web_url("inbox", 
				"URL=https://mail.yandex.ru/lite/inbox", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Snapshot=t221.inf", 
				"Mode=HTML", 
				LAST);
	    
		}

	lr_end_transaction("�������� ������������� ��������� � �����", LR_AUTO);
	

	return 0;
}