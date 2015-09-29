vuser_end()
{
	lr_start_transaction("Выход");
	
		web_url("passport_2", 
			"URL=https://passport.yandex.ru/passport?mode=logout&yu=5827752021443444761"	//Ссылка верна для любого аккаунта и сессии
			"Resource=0",
			"RecContentType=text/html", 
			"Snapshot=t108.inf", 
			"Mode=HTML", 
			LAST);
	
	lr_end_transaction("Выход", LR_AUTO);
	
	return 0;
}
