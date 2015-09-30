Action()
{
	int elemCnt;
	
	int x;
	
	char arrayParamName[50]; 
		
	
	lr_start_transaction("Выбор только непрочитанных сообщений");

		web_reg_find("Text=Входящие", 
			LAST);
		
		//Сохраняем id всех непрочитанных сообщений
		web_reg_save_param_ex(
			"ParamName=MESSAGE_ID",
		    "LB/IC=<span class=\"b-messages__message__left\" href=\"/lite/message/",
			"RB/IC=/new\">",
			"NotFound=warning", 	//На случай, если нет непрочитанных сообщений
			"Ordinal=all",
			SEARCH_FILTERS,
		  	"Scope=body", 
		  	LAST);
		
		//Сохраняем yandex_uid для выхода из почты в дальнейшем
		web_reg_save_param_ex(
			"ParamName=LOGOUT_ID",
			"LB=mode=logout&amp;yu=",
			"RB=&amp;",
			SEARCH_FILTERS,
			"Scope=BODY",
			LAST);

		web_url("unread", 
			"URL=https://mail.yandex.ru/lite/unread", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t219.inf", 
			"Mode=HTML", 
			LAST);
		
		elemCnt = atoi(lr_eval_string("{MESSAGE_ID_count}"));

		lr_output_message("Число непрочитанных сообщений = %d", elemCnt);
		
	lr_end_transaction("Выбор только непрочитанных сообщений", LR_AUTO);
	
	
	lr_start_transaction("Просмотр непрочитанных сообщений в цикле");
	
		for (x = 1; x <= elemCnt; x++) {
		
		    sprintf(arrayParamName, "{MESSAGE_ID_%d}", x);
		    
		    lr_save_string(lr_eval_string(arrayParamName), "id");
      
			//Открытие письма
			web_reg_find("Text=Входящие", 
				LAST);
			
			web_url("{id}/new", 
				"URL=https://mail.yandex.ru/lite/message/{id}/new", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Snapshot=t220.inf", 
				"Mode=HTML", 
				LAST);
		    
			//Возврат во входящие
			web_reg_find("Text=Входящие", 
				LAST);		
			
			web_url("inbox", 
				"URL=https://mail.yandex.ru/lite/inbox", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Snapshot=t221.inf", 
				"Mode=HTML", 
				LAST);
	    
		}

	lr_end_transaction("Просмотр непрочитанных сообщений в цикле", LR_AUTO);
	
	return 0;
}