package com.mickey;

public class Person
{
	int need,ID,ghiseu;
	long startTime;
	Person(int nrNeed,int nrOrdine,int ghis)
	{
		ghiseu=ghis;
		need = nrNeed;
		ID = nrOrdine;
		startTime = System.currentTimeMillis();
	}

	int getNeed()
	{
		return need;
	}

	public void finnish()
	{
		long currentTime = (System.currentTimeMillis());
		System.out.println("Persoana "+ID+" e gata. A durat:"+(currentTime-startTime));
		Agency.updateTime(currentTime-startTime,ghiseu);
	}
}
