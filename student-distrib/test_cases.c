/*TESTCASES FOR CP 2 AND OTHER RANDOM TESTCASES*/

	/*Check for RTC*/
	
	/*
	clear();
	int a = 1;
	int b = 0;
	uint32_t rtc_test_buf[1];
	rtc_test_buf[0]=2048;

	open_rtc((const uint8_t*)0);
	write_rtc(0,(const void*)rtc_test_buf,4);
	printf("frequency: %d ", rtc_test_buf[0]);
	for(b = 0; b<10; b++)
	{
		printf("%d", b);
		read_rtc(0,0,0);
	}


	for(a = 2; a <= 1024; a=a*2)
	{
		rtc_test_buf[0]=a;
		printf("\n");
		write_rtc(0,(const void*)rtc_test_buf,4);
		printf("frequency: %d ", a);
		for(b = 0; b<10; b++)
		{
			printf("%d", b);
			read_rtc(0,0,0);
		}
	}
	*/

	/* Testing for terminal read, write */

	/*	
	unsigned char terminal_read_test_buf[128];

	read_terminal(0, terminal_read_test_buf, 0);
	write_terminal(0, terminal_read_test_buf, 0);
	read_terminal(0, terminal_read_test_buf, 0);
	write_terminal(0, terminal_read_test_buf, 0);	

	int32_t	bytes_read = read_terminal(0, terminal_read_test_buf, 0);
	bytes_read = write_terminal(0, terminal_read_test_buf, 0);
	*/

	
	//int32_t test_var;
	/* tests for checking if file_open works correctly */
	
	/*
	test_var = file_open((uint8_t*)"verylargetxtwithverylongname");
	printf("test_var = %d\n", test_var);
	test_var = file_open((uint8_t*)"verylargetxtwithverylongname.tx");
	printf("test_var = %d\n", test_var);
	test_var = file_open((uint8_t*)"ekalfh");
	printf("test_var = %d\n", test_var);
	test_var = file_open((uint8_t*)"frame0");
	printf("test_var = %d\n", test_var);
	test_var = file_open((uint8_t*)"frame0.txt");
	printf("test_var = %d\n", test_var);
	test_var = file_open((uint8_t*)"frame0.tx");
	printf("test_var = %d\n", test_var);
	test_var = file_open((uint8_t*)"frame02");
	printf("test_var = %d\n", test_var);
	*/
	
	
	/* tests for checking if files can be read */
	
	/*
	int k; // iterator
	unsigned char file_buf1[1000];
	
	test_var = file_read(1, file_buf1, 15);
	printf("buffer has %d bytes\n", test_var);
	for (k = 0; k < test_var; k++)
		printf("%c", file_buf1[k]);
	printf("\n");
	
	test_var = file_read(2, file_buf1, 10);
	printf("buffer has %d bytes\n", test_var);
	for (k = 0; k < test_var; k++)
		printf("%c", file_buf1[k]);
	printf("\n");
	
	test_var = file_read(2, file_buf1, 101);
	printf("buffer has %d bytes\n", test_var);
	for (k = 0; k < test_var; k++)
		printf("%c", file_buf1[k]);
	printf("\n");
	
	test_var = file_read(2, file_buf1, 102);
	printf("buffer has %d bytes\n", test_var);
	for (k = 0; k < test_var; k++)
		printf("%c", file_buf1[k]);
	printf("\n");
	
	test_var = file_read(3, file_buf1, 12);
	printf("buffer has %d bytes\n", test_var);
	for (k = 0; k < test_var; k++)
		printf("%c", file_buf1[k]);
	printf("\n");
	
	test_var = file_read(64, file_buf1, 12);
	printf("buffer has %d bytes\n", test_var);
	
	test_var = file_read(40, file_buf1, 24);
	printf("buffer has %d bytes\n", test_var);
	*/
	
	
	
	/* tests for checking if dir_open works */
	
	/*
	test_var = dir_open((const uint8_t*)".");
	printf("test_var = %d\n", test_var);
	test_var = dir_open((const uint8_t*)"ahfa");
	printf("test_var = %d\n", test_var);
	*/
	
	
	/* tests for checking if dir_read works */
	
	
	//unsigned char dir_buf1[32];
	//int k; // iterators
	// check that dir_read starts over at index 0 when dir_open is called
	/*
	test_var = dir_open((const uint8_t*)".");
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 32);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 32);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 4);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 32);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 32);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_open((const uint8_t*)".");
	test_var = dir_read(0, dir_buf1, 32);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 32);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	test_var = dir_read(0, dir_buf1, 7);
	for (k = 0; k < test_var; k++)
		printf("%c", dir_buf1[k]);
	printf("\n");
	*/

	/* print all file names*/
	/*
	int n;
	
	file_boot_struct_t* boot_block = (file_boot_struct_t*)base_file_addr;
	for (n = 0; n < boot_block->num_dir_entries; n++){
		test_var = dir_read(196, dir_buf1, 32);
		for (k = 0; k < test_var; k++)
			printf("%c", dir_buf1[k]);
		printf("\n");
	}
	*/
	

	/*RANDOM TESTS*/

	/*
	unsigned char str[32]="verylargetxtwithverylongname.tx";
	dentry_t dentry_test;
	int length = 2000;
	int offset = 0;
	uint8_t buf[length];
	
	read_dentry_by_name (str, &dentry_test);
	//int place = 27;
	//read_dentry_by_index (place, &dentry_test);
	int z = read_data(dentry_test.inode_index,offset,buf,length);
	printf("ret val : %d\n", z);
	
	int k=0;
	for(k = 0; k < z; k++)
	{
		printf("%c", buf[k]);
	}
	*/	
	



