
vuser_init()
{
	
	lr_start_transaction("���� �� ����");
	
		web_reg_find("Text=������", 
			LAST);
	
		web_url("yandex.ru", 
			"URL=http://yandex.ru/", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t209.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("���� �� ����", LR_AUTO);

	lr_start_transaction("�������� �������� �����������");
	
		web_reg_find("Text=������.����� � ���������� ����������� �����", 
			LAST);
	
		web_url("mail.yandex.ru", 
			"URL=https://mail.yandex.ru/", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t215.inf", 
			"Mode=HTML", 
			LAST);
		
		web_reg_find("Text=�����������", 
			LAST);
	
		web_url("lite", 
			"URL=https://mail.yandex.ru/lite", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Snapshot=t217.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("�������� �������� �����������", LR_AUTO);
	
	lr_start_transaction("�����������");
	
		web_reg_find("Text=��������", 
			LAST);
	
		web_submit_data("passport", 
			"Action=https://passport.yandex.ru/passport?mode=auth", 
			"Method=POST", 
			"RecContentType=text/html", 
			"Snapshot=t218.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=login", "Value={LOGIN}", ENDITEM, 
			"Name=passwd", "Value={PASSWORD}", ENDITEM, 
			"Name=retpath", "Value=https://mail.yandex.ru/lite/inbox", ENDITEM, 
			LAST);
	
	lr_end_transaction("�����������", LR_AUTO);
	
	return 0;
}