Action()
{

	lr_start_transaction("�������� ����� ��� ������ ������");
	
		web_reg_find("text=����� ������ � ������.�����", 
			LAST);
	
		web_url("retpath=inbox", 
			"URL=https://mail.yandex.ru/lite/compose/", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t13.inf", 
			"Mode=HTML", 
			LAST);
	
	lr_end_transaction("�������� ����� ��� ������ ������", LR_AUTO);
	
	lr_start_transaction("�������� ������");
	
		web_submit_form("create_message.xml", 
			"Snapshot=t14.inf", 
			ITEMDATA, 
			"Name=request", "Value=", ENDITEM, 
			"Name=to", "Value={LOGIN}", ENDITEM, 
			"Name=cc", "Value=", ENDITEM, 
			"Name=bcc", "Value=", ENDITEM, 
			"Name=subj", "Value={SUBJECT}", ENDITEM, 
			"Name=send", "Value={MESSAGEBODY}", ENDITEM, 
			"Name=att", "Value=", "File=Yes", ENDITEM, 
			"Name=doit", "Value=���������", ENDITEM, 
			LAST);
	
		web_reg_find("Text=������ ����������", 
			LAST);
	
		web_url("inbox", 
			"URL=https://mail.yandex.ru/lite/inbox?ids=&executed_action=message_send", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t15.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("�������� ������", LR_AUTO);
	
	return 0;
}
