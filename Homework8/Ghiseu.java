package com.mickey;

import java.util.ArrayDeque;

public class Ghiseu implements Runnable
{
	int[] operatii;
	int nrOperatii,peopleWaiting,ID;
	ArrayDeque<Person> deq = new ArrayDeque<>();
	Ghiseu(int[]op,int nrOp,int nrGhiseu)
	{
		operatii=op;
		nrOperatii=nrOp;
		peopleWaiting=0;
		ID = nrGhiseu;
	}

	boolean canFill(int OP)
	{
		for(int i=0;i<nrOperatii;i++)
			if(operatii[i]==OP)
				return true;
		return false;
	}

	public int getPeopleWaiting()
	{
		return peopleWaiting;
	}

	public int getID()
	{
		return ID;
	}

	public void addPerson(Person person)
	{
		deq.offerLast(person);
		peopleWaiting++;
	}

	@Override
	public void run()
	{
		Thread thread = new Thread(() ->
		{
			while(true)
			{
				while (deq.isEmpty() == false)
				{
					Person person = deq.pollFirst();
					person.finnish();
					peopleWaiting--;
					try
					{
						Thread.sleep(2000);
					}
					catch (InterruptedException e)
					{
						e.printStackTrace();
					}
				}
				try
				{
					Thread.sleep(1000);
				}
				catch (InterruptedException e)
				{
					e.printStackTrace();
				}
			}
		});
		thread.start();
	}
}
