package com.mickey;

import java.util.ArrayList;
import java.util.Scanner;

public class Main
{

    public static void main(String[] args)
	{
		int nrNevoi=0;
		Scanner in = new Scanner(System.in);
		System.out.println("Cate ghisee sa aiba agentia?:");
		int nrGhisee = in.nextInt();
		ArrayList<Ghiseu> ghisee = new ArrayList<Ghiseu>();
		for(int i=0;i<nrGhisee;i++)
		{
			System.out.println("Cate operatii poate efectua ghiseul "+i);
			int nrOp = in.nextInt();
			System.out.println("Ce operatii poate efectua ghiseul "+i);
			int[] operations = new int[10];
			for(int j=0;j<nrOp;j++)
			{
				operations[j]=in.nextInt();
				nrNevoi = Math.max(nrNevoi,operations[j]);
			}
			Ghiseu ghiseu = new Ghiseu(operations,nrOp,i);
			ghisee.add(ghiseu);
		}
		Agency agency = new Agency(ghisee,nrGhisee,nrNevoi);
		agency.open();
    }
}
