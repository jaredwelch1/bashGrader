TEST(allocation_test, test_not_null){
	Person *list = NULL;

	list = allocate_memory();

	score+=5;
	allocate_not_null = false;
	free_list(list);

}

TEST(allocation_test, test_size_correct){
	Person *list = NULL;

	list = malloc(sizeof(Person) * 5);

	Person *studentList = allocate_memory();

	//ASSERT_EQ(sizeof(list))
	//Find correct size of the memory locations to be equal
	//free that stuff
}

//chance of seg fault so put at end? 
TEST(insert_contacts, test_insert_contacts){
	Person *list = allocate_memory();
	//+5 for one
	//+5 more for rest
}


//these will be like 2 points each, 8 total? Valid should just return 1 so I think that is fair, free 4 points
TEST(test_email_validator, invalid email){
}

TEST(test_email_validator, valid email){
}

TEST(test_phone_validator, invalid_num){
}

TEST(test_phone_validator, valid_num){
}

//last 10 from their memory leaking or not 
//7 for free? Maybe add more into add_contact stuff...
