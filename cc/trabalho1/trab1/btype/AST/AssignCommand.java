/* AssignCommand.java
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */
 
package trab1.btype.AST;

import java.util.*;

public class AssignCommand extends Command {

    public AssignCommand( Variable var, Value val ) {
        this.variable = var;
        this.value = val;
    }
    
    public void genC() {
        System.out.print( variable.value + " = " + value.value + ";\n" );
    }
    
    private Variable variable;
    private Value value;}
