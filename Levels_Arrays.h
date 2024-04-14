#pragma once



class AsLevels_Arrays
{
protected:
	~AsLevels_Arrays();
	AsLevels_Arrays();

public:
	AsLevels_Arrays(AsLevels_Arrays& other) = delete;
	void operator=(const AsLevels_Arrays&) = delete;

	static unsigned char Level_Test[30][70];
	static unsigned char Level_1[22][50];
	static unsigned char Level_2[18][48];

private:
};