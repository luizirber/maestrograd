/* CompilerB.java
 *
 * Based on Compiler 06.
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.btype;

import trab1.btype.AST.*;
import trab1.ParseException;
import java.util.*;
import java.lang.Character;
public class CompilerB {

    public Program compile(char []p_input) {
        input = p_input;
        tokenPos = 0;
        nextToken();
        try {
            Program result = program();
            return result;
        }
        catch (ParseException e) {}
        return null;
    }
    
    private Program program() throws ParseException {
        Vector<Command> arrayCommand = new Vector();
        arrayCommand.addElement ( command() );
        while ( token != '\0')
            arrayCommand.addElement ( command() );
        return new Program ( arrayCommand );
    }
    
    private Command command() throws ParseException {
        switch (token) {
            case 'R': return readCommand();
            case 'N': return incCommand();
            case 'D': return decCommand();
            case 'P': return printCommand();
            case 'I': return ifCommand();
            case 'W': return whileCommand();
            case '[': return compositeCommand();
            default: if ( token <= 'z' && token >= 'a' )
                         return assignCommand();
                     else
                         throw new ParseException("No such command", input, tokenPos);
        }
    }
    
    private ReadCommand readCommand() throws ParseException {
        nextToken();
        return new ReadCommand( variable() );
    }
    
    private IncCommand incCommand() throws ParseException {
        nextToken();
        return new IncCommand( variable() );
    }
    
    private DecCommand decCommand() throws ParseException {
        nextToken();
        return new DecCommand( variable() );   
    }
    
    private PrintCommand printCommand() throws ParseException {
        nextToken();
        return new PrintCommand( value() );
    }
    
    private IfCommand ifCommand() throws ParseException {
        nextToken();
        Value val = value();
        return new IfCommand( val, command() );
    }
    
    private WhileCommand whileCommand() throws ParseException {
        nextToken();
        Value val = value();
        return new WhileCommand( val, command() );
    }
    
    private CompositeCommand compositeCommand() throws ParseException {
        nextToken();
        Vector<Command> commandList = new Vector();
        commandList.addElement( command() );
        while (token != ']') {
            commandList.addElement( command() );
        }
        nextToken();
        return new CompositeCommand( commandList );
    }
    
    private AssignCommand assignCommand() throws ParseException {
        Variable var = variable();
        nextToken();
        return new AssignCommand( var, value() );
    }
    
    private Value value() throws ParseException {
        Value val;
        if ( token <= 'z' && token >= 'a' )
            val = variable();
        else
            val = number();
        return val;
    }
    
    private Numb number() throws ParseException {
        if ( token <= '9' && token >= '0' ) {
            char val = token;
            nextToken();
            return new Numb( val );
        }
        else
            throw new ParseException("Must be a number", input, tokenPos);
    }
    
    private Variable variable() throws ParseException {
        if ( token <= 'z' && token >= 'a' ) {
            char val = token;
            nextToken();
            return new Variable( val );
        }
        else
            throw new ParseException("Must be a variable", input, tokenPos);
    }
    
    
    private void nextToken() {
        while ( tokenPos < input.length && (input[tokenPos] == ' ' || input[tokenPos] == '\n'))
            tokenPos++;
        if ( tokenPos < input.length ) {
            token = input[tokenPos];        
            tokenPos++;
        }
        else
            token = '\0';
    }
    
    private char token;
    private int  tokenPos;
    private char []input;

}

