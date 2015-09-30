Action()
{

	lr_start_transaction("Открытие формы для нового письма");
	
		web_reg_find("text=Новое письмо — Яндекс.Почта", 
			LAST);
	
		//Сохраняем yandex_uid для выхода из почты в дальнейшем
		web_reg_save_param_ex(
			"ParamName=LOGOUT_ID",
			"LB=mode=logout&amp;yu=",
			"RB=&amp;",
			SEARCH_FILTERS,
			"Scope=BODY",
			LAST);
	
		web_url("retpath=inbox", 
			"URL=https://mail.yandex.ru/lite/compose/", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t13.inf", 
			"Mode=HTML", 
			LAST);
	
	lr_end_transaction("Открытие формы для нового письма", LR_AUTO);
	
	lr_start_transaction("Отправка письма");
	
		web_submit_form("compose-send", 
			"Snapshot=t14.inf", 
			ITEMDATA, 
			"Name=request", "Value=", ENDITEM, 
			"Name=to", "Value={LOGIN}", ENDITEM, 
			"Name=cc", "Value=", ENDITEM, 
			"Name=bcc", "Value=", ENDITEM, 
			"Name=subj", "Value={SUBJECT}", ENDITEM, 
			"Name=send", "Value={MESSAGEBODY}", ENDITEM, 
			"Name=att", "Value=", "File=Yes", ENDITEM, 
			"Name=doit", "Value=Отправить", ENDITEM, 
			LAST);
	
		web_reg_find("Text=Письмо отправлено", 
			LAST);
	
		web_url("inbox", 
			"URL=https://mail.yandex.ru/lite/inbox?ids=&executed_action=message_send", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t15.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("Отправка письма", LR_AUTO);
	
	return 0;
}
