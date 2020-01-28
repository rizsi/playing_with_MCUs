

import java.util.TreeMap;

public class Divisors {
	static class Range
	{
		int row;
		int col;
		int readout;
		int minLimit;
		int maxLimit=-1;
		int index;	// Index of the button in the uC application
		char ch; // Label of the button
	}
	public static void main(String[] args) {
		int indexes[]={1, 2, 3,
						4, 5, 6,
						7, 8, 9,
						10, 0, 11
		};
		char chars[]={'1', '2', '3',
				'4', '5', '6',
				'7', '8', '9',
				'*', '0', '#'
		};
		int colValues[]={150,197,244};
		int rowValues[]={47+47+150+330,47+47+150,47+47,47};
		TreeMap<Integer, Range> readouts=new TreeMap<>();
		for(int col=0;col<3;++col)
		{
			for(int row=0;row<4;++row)
			{
				int readout=(1024*rowValues[row])/(colValues[col]+rowValues[row]);
				Range r=new Range();
				r.col=col;
				r.row=row;
				r.readout=readout;
				r.index=indexes[row*3+col];
				r.ch=chars[row*3+col];
				readouts.put(readout, r);
			}
		}
		Range prev=new Range();
		for(Integer i:readouts.keySet())
		{
			Range r=readouts.get(i);
			int limit=prev.readout+(i-prev.readout)/2;
			r.minLimit=limit;
			prev.maxLimit=limit;
			System.out.println("limit: "+limit+" value: "+i+" -> "+readouts.get(i).ch+" diff: "+(i-prev.readout));
			prev=r;
		}
		for(Integer i:readouts.keySet())
		{
			Range r=readouts.get(i);
			System.out.println("if(value>="+r.minLimit+(r.maxLimit>-1?"&&value<"+r.maxLimit:"")+") pressedIndex="+r.index+"; // '"+r.ch+"'");
		}
	}
}

