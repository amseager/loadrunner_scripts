vuser_end()
{
	lr_start_transaction("�����");
	
		web_url("passport_2", 
			"URL=https://passport.yandex.ru/passport?mode=logout&yu=5827752021443444761"	//������ ����� ��� ������ �������� � ������
			"Resource=0",
			"RecContentType=text/html", 
			"Snapshot=t108.inf", 
			"Mode=HTML", 
			LAST);
	
	lr_end_transaction("�����", LR_AUTO);
	
	return 0;
}
