Action()
{
	int elemCnt;
	
	int x;
	
	char arrayParamName[50]; 		
	
	lr_start_transaction("Выбор непрочитанных сообщений с 'Test 1' в теме");

		web_reg_find("Text=Входящие", 
			LAST);

		//Сохраняем id всех сообщений с 'Test 1' в теме
		web_reg_save_param_regexp(
			"ParamName=MESSAGE_ID",
			"RegExp=<a href=\"\\/lite\\/message\\/(\\d+)\\/new\" class=\"b-messages__message__link\" aria-label=([\"'])[^\\\\2]*?(?:Test 1)[^\\\\2]*?\\2>",
			"NotFound=warning",
			"Ordinal=all",
			SEARCH_FILTERS,
			"Scope=BODY",
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

		lr_output_message("Число непрочитанных сообщений с 'Test 1' в теме = %d", elemCnt);
		
	lr_end_transaction("Выбор непрочитанных сообщений с 'Test 1' в теме", LR_AUTO);
	
	lr_start_transaction("Ответ на сообщения в цикле");
	
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
		
		    // Отправка ответа на письмо
		    
		    web_reg_find("Text=Входящие", 
				LAST);

			web_submit_form("compose-action.xml", 
				"Snapshot=t10.inf", 
				ITEMDATA, 
				"Name=send", "Value=Ответ на сообщение с id {id}", ENDITEM, 
				"Name=doit", "Value=Отправить", ENDITEM, 
				LAST);
		    
		    //Успешное возвращение во Входящие
		    
			web_reg_find("Text=Письмо отправлено", 
				LAST);
		
			web_url("inbox", 
				"URL=https://mail.yandex.ru/lite/inbox?ids=&executed_action=message_send", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Snapshot=t15.inf", 
				"Mode=HTML", 
				LAST);
		   
	    }

	lr_end_transaction("Ответ на сообщения в цикле", LR_AUTO);

	return 0;
}