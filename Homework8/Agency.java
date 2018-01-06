package com.mickey;

import java.util.ArrayList;
import java.util.Random;

public class Agency
{
	int nrGhisee,nrNevoi;
	static int clientsServed;
	ArrayList<Ghiseu> ghisee;
	static long totalTime;
	static int[] freq,waitTime;
	static void updateTime(long time,int ghiseu)
	{
		totalTime+=time;
		clientsServed++;
		freq[ghiseu]++;
		waitTime[ghiseu]+=time;
	}

	Agency(ArrayList<Ghiseu> gh,int nrGh,int nrNev)
	{
		totalTime=0;
		freq = new int[100];
		waitTime = new int[100];
		clientsServed=0;
		nrGhisee=nrGh;
		ghisee=gh;
		for(Ghiseu ghiseu :ghisee)
			ghiseu.run();
		nrNevoi=nrNev;
	}

	void open()
	{
		int nrOrdine=0;
		while(true)
		{
			Random rand= new Random();
			int nrPersoane = (rand.nextInt()& Integer.MAX_VALUE)%7 +1;
			System.out.println(nrPersoane+" persoane au venit la agentie.");
			for(int i=1;i<=nrPersoane;i++)
			{
				nrOrdine++;
				int personNeed = (rand.nextInt()& Integer.MAX_VALUE)%nrNevoi;
				int minPeopleWaiting = 1<<30;
				int ghiseuID=0;
				for(Ghiseu gh:ghisee)
					if(gh.canFill(personNeed)&&gh.getPeopleWaiting()<minPeopleWaiting)
					{
						minPeopleWaiting = gh.getPeopleWaiting();
						ghiseuID = gh.getID();
					}
				Person person = new Person(personNeed,nrOrdine,ghiseuID);
				for(Ghiseu gh:ghisee)
					if(gh.getID()==ghiseuID)
					{
						gh.addPerson(person);
						System.out.println("Persoana cu Id-ul "+person.ID+" si nevoia "+person.need+" se aseaza la ghiseul "+gh.getID());
					}
			}
			displayStats();
			try
			{
				Thread.sleep(3000);
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}

	private void displayStats()
	{
		System.out.println("Timpul total de asteptare este "+totalTime);
		System.out.println("Media timpului de asteptare pentru un client este "+(((double)totalTime))/((double)clientsServed));
		System.out.println("Cate persoane asteapta la fiecare ghiseu: ");
		int totalPeople=0;
		for(Ghiseu gh:ghisee)
		{
			System.out.println("La ghiseul cu ID-ul "+gh.ID+" Asteapta "+gh.peopleWaiting+" Medie timp: "+(((double)waitTime[gh.ID]))/((double)freq[gh.ID]));
			totalPeople+=gh.peopleWaiting;
		}
		System.out.println("Total persoane care asteapta: "+totalPeople);
	}
}
