/* CompilerA.java
 *
 * Based on Compiler 03.
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.atype;

import trab1.ParseException;
import java.util.*;
import java.lang.Character;


public class CompilerA {
    public void compile ( char []p_input) {
        input = p_input;
        tokenPos = 0;
        nextToken();
        System.out.print("#include <stdio.h>\n");
        System.out.print("\nint main( void ) {\n");
        System.out.print("    int a = 0, ");       
        for (char ch='b'; ch < 'z'; ch++)
            System.out.print( ch + " = 0, ");
        System.out.print("z = 0;\n");
        try {
            command();
            while (token != '\0')
                command();
        }
        catch (ParseException error) {
        }
        System.out.print("\n    return 0;\n}\n");
    }
    
    private void command() throws ParseException {
        System.out.print("    ");
        switch (token) {
            case 'R': readCommand();
                      break;
            case 'N': incCommand();
                      break;
            case 'D': decCommand();
                      break;
            case 'P': printCommand();
                      break;
            case 'I': ifCommand();
                      break;
            case 'W': whileCommand();
                      break;
            case '[': compositeCommand();
                      break;
            default: if ( token <= 'z' && token >= 'a' )
                         assignCommand();
                     else
                         throw new ParseException("No such command", input, tokenPos);
        }
    }

    private void readCommand() throws ParseException {
        nextToken();
        System.out.print("printf(\"What is the value of variable? \");\n");
        System.out.print("    ");
        System.out.print("scanf(\"%d\", &");
        variable();
        System.out.print(");\n");
    }
    
    private void incCommand() throws ParseException {
        nextToken();
        variable();
        System.out.print("++;\n");
    }
    
    private void decCommand() throws ParseException {
        nextToken();
        variable();
        System.out.print("--;\n");        
    }
    
    private void printCommand() throws ParseException {
        nextToken();
        System.out.print("printf(\"%d\\n\", ");
        value();
        System.out.print(");\n");
    }
    
    private void ifCommand() throws ParseException {
        nextToken();
        System.out.print("if (");
        value();
        System.out.print(" != 0)\n");
        command();
    }
    
    private void whileCommand() throws ParseException {
        nextToken();
        System.out.print("while (");        
        value();
        System.out.print(" != 0 ) \n");        
        command();
    }
    
    private void compositeCommand() throws ParseException {
        System.out.print("{\n    ");
        nextToken();
        command();
        while (token != ']') {
            System.out.print("    ");        
            command();
        }
        nextToken();
        System.out.print("    }\n");        
    }
    
    private void assignCommand() throws ParseException {
        variable();
        nextToken();
        System.out.print(" = ");
        value();
        System.out.print(";\n");
    }
    
    private void value() throws ParseException {
        if ( token <= 'z' && token >= 'a' )
            variable();
        else
            number();
    }
    
    private void number() throws ParseException {
        if ( token <= '9' && token >= '0' )
            System.out.print(token);
        else
            throw new ParseException("Must be a number", input, tokenPos);
        nextToken();
    }
    
    private void variable() throws ParseException {
        if ( token <= 'z' && token >= 'a' )
            System.out.print(token);
        else
            throw new ParseException("Must be a variable", input, tokenPos);
        nextToken();
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

