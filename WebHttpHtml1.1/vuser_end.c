vuser_end()
{
	lr_start_transaction("Выход");
	
		web_reg_find("Text=Почта",
			LAST);

		web_url("passport_2", 
			"URL=https://passport.yandex.ru/passport?mode=logout&yu={LOGOUT_ID}",
			"Resource=0",
			"RecContentType=text/html", 
			"Snapshot=t108.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("Выход", LR_AUTO);
	
	return 0;
}
