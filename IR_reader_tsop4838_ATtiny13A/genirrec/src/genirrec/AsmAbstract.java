package genirrec;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Stack;

import hu.qgears.rtemplate.runtime.DummyCodeGeneratorContext;
import hu.qgears.rtemplate.runtime.RAbstractTemplatePart;

public class AsmAbstract extends RAbstractTemplatePart {
	private String currentSwitch;
	private boolean caseOpen=false;
	private Stack<StackFrame> stackFrames=new Stack<>();
	private List<String> cases=new ArrayList<>();
	private int labelIndex;
	private Stack<String> currentLabelPrefix=new Stack<>();
	private Set<String> labels=new HashSet<>();
	protected int allItStack=0;
	class StackFrame
	{
		boolean saveRegsIt=false;
		List <String> savedRegs=new ArrayList<>();
	}

	public AsmAbstract() {
		super(new DummyCodeGeneratorContext());
		currentLabelPrefix.push("no_context");
	}
	protected void finish() {
		if(stackFrames.size()>0)
		{
			throw new RuntimeException("Unclosed stack frame!");
		}
		finishDeferredParts();
		if(stackFrames.size()>0)
		{
			throw new RuntimeException("Unclosed stack frame!");
		}
		System.out.println(getTemplateState().getOut().toString());
	}
	
	protected void endSwitch() {
		if(caseOpen)
		{
			currentLabelPrefix.pop();
		}
		writeObject(currentSwitch);
		write("_end:\n");
		currentLabelPrefix.pop();
	}
	protected void saveRegsIt(String... regsToSave) {
		int size=3+regsToSave.length;
		allItStack+=size;
		write("    // SAVE REGS in interrupt. Stack frame size: ");
		writeObject(size);
		write(" bytes\n    push r0\n    in r0,_SFR_IO_ADDR(SREG)\n");
		_saveRegs(regsToSave);
		stackFrames.peek().saveRegsIt=true;
	}
	protected void saveRegs(String... regsToSave) {
		int size=2+regsToSave.length;
		write("    // SAVE REGS Stack frame size: ");
		writeObject(size);
		write(" bytes\n");
		_saveRegs(regsToSave);
	}
	private void _saveRegs(String[] regsToSave) {
		stackFrames.push(new StackFrame());
		for(String s: regsToSave)
		{
			write("    push ");
			writeObject(s);
			write("\n");
			stackFrames.peek().savedRegs.add(s);
		}
	}
	protected void restoreRegs()
	{
		write("    // RESTORE SAVED REGS (");
		writeObject(stackFrames.peek().savedRegs);
		write(")\n");
		Collections.reverse(stackFrames.peek().savedRegs);
		for(String s: stackFrames.peek().savedRegs)
		{
			write("    pop ");
			writeObject(s);
			write("\n");
		}
		if(stackFrames.peek().saveRegsIt)
		{
			write("    out _SFR_IO_ADDR(SREG), r0\n    pop r0\n");
		}
		stackFrames.pop();
	}
	protected void caseValue(String string) {
		if(caseOpen)
		{
			currentLabelPrefix.pop();
			write("    rjmp ");
			writeObject(currentSwitch);
			write("_end\n");
		}
		currentLabelPrefix.push(currentLabelPrefix.peek()+"_"+string);
		cases.add(string);
		write("\n");
		writeObject(currentSwitch);
		write("_");
		writeObject(string);
		write(":\n");
		caseOpen=true;
	}

	protected void startSwitch(String id, String swVariable, String tempVariable) {
		currentSwitch=id;
		currentLabelPrefix.push(currentSwitch);
		write("    ldi\tZL, lo8(pm(");
		writeObject(id);
		write("_sw_table))\n    ldi\tZH, hi8(pm(");
		writeObject(id);
		write("_sw_table))\n    ldi ");
		writeObject(tempVariable);
		write(", 0\n\n    cpi ");
		writeObject(swVariable);
		write(", ");
		writeObject(currentSwitch);
		write("_COUNT\n    BRLT ");
		writeObject(currentSwitch);
		write("_jump\n    ldi ");
		writeObject(swVariable);
		write(", 0 // In case of invalid state reset to state 0\n");
		writeObject(currentSwitch);
		write("_jump:\n    add ZL, ");
		writeObject(swVariable);
		write("\n    adc ZH, ");
		writeObject(tempVariable);
		write("\n    ijmp\n");
		deferred(this::generateSwitchTable);
		caseOpen=false;
	}
	protected void generateSwitchTable(Object[] param)
	{
		writeObject(currentSwitch);
		write("_sw_table:\n");
		for(String s: cases)
		{
			write("    rjmp ");
			writeObject(currentSwitch);
			write("_");
			writeObject(s);
			write("\n");
		}
	}
	protected void generateSwitchStates()
	{
		deferred(this::generateSwitchStatesPrivate);
	}
	private void generateSwitchStatesPrivate(Object[] param)
	{
		int caseIndex=0;
		for(String s: cases)
		{
			write("#define ");
			writeObject(s);
			write(" ");
			writeObject(caseIndex);
			write("\n");
			caseIndex++;
		}
		write("#define ");
		writeObject(currentSwitch);
		write("_COUNT ");
		writeObject(caseIndex);
		write("\n");
	}
	protected String createLabel(String name)
	{
		String ret=currentLabelPrefix.peek()+"_"+name;
		if(!labels.add(ret))
		{
			ret=ret+"_"+labelIndex;
			labels.add(ret);
		}
		labelIndex++;
		return ret;
	}
	protected void printAllStackSize(Object[] args)
	{
		writeObject(allItStack);
	}
}
