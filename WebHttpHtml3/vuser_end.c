vuser_end()
{
	lr_start_transaction("�����");
	
		web_reg_find("Text=�����",
			LAST);

		web_url("passport_2", 
			"URL=https://passport.yandex.ru/passport?mode=logout&yu={LOGOUT_ID}",
			"Resource=0",
			"RecContentType=text/html", 
			"Snapshot=t108.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("�����", LR_AUTO);
	
	return 0;
}
