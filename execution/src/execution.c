/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfouadi <mfouadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:39:29 by mfouadi           #+#    #+#             */
/*   Updated: 2023/04/08 06:27:16 by mfouadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*


Implement redirections:
	◦< should redirect input.
	◦> should redirect output.
	◦<< should be given a delimiter, then read the input until a line containing the
	delimiter is seen. However, it doesn’t have to update the history!
	◦>> should redirect output in append mode.
	•Implement pipes (| character). The output of each command in the pipeline is
	connected to the input of the next command via a pipe.
	•Handle environment variables ($ followed by a sequence of characters) which
	should expand to their values.
	•Handle $? which should expand to the exit status of the most recently executed
	foreground pipeline.

•Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
	•In interactive mode:
	◦ctrl-C displays a new prompt on a new line.
	◦ctrl-D exits the shell.
	◦ctrl-\ does nothing.
	•Your shell must implement the following builtins:
	◦echo with option -n
	◦cd with only a relative or absolute path
	◦pwd with no options
	◦export with no options
	◦unset with no options
	◦env with no options or arguments
	◦exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.
*/

//   <<     EOF  cat  -e   |  cat   >  outfile  |  echo "More"  >>  outfile  |  echo  $PATH
// HEREDOC LMTR  CMD  FLG  PP CMD TRNC   TR_F   PP  CMD   ARG  APND  AP_F    PP CMD  ARG

// $? prints exit status

// 3.1.1 Shell Operation
	// The following is a brief description of the shell’s operation when it reads and executes a
	// command. Basically, the shell does the following:
	// 1. Reads its input from a file (see Section 3.8 [Shell Scripts], page 46), from a string
	// supplied as an argument to the -c invocation option (see Section 6.1 [Invoking Bash],
	// page 91), or from the user’s terminal.
	// 2. Breaks the input into words and operators, obeying the quoting rules described in
	// Section 3.1.2 [Quoting], page 6. These tokens are separated by metacharacters. Alias
	// expansion is performed by this step (see Section 6.6 [Aliases], page 100).
	// 3. Parses the tokens into simple and compound commands (see Section 3.2 [Shell Com-
	// mands], page 9).
	// 4. Performs the various shell expansions (see Section 3.5 [Shell Expansions], page 24),
	// breaking the expanded tokens into lists of filenames (see Section 3.5.8 [Filename Ex-
	// pansion], page 35) and commands and arguments.
	// 5. Performs any necessary redirections (see Section 3.6 [Redirections], page 38) and re-
	// moves the redirection operators and their operands from the argument list.
	// 6. Executes the command (see Section 3.7 [Executing Commands], page 42).
	// 7. Optionally waits for the command to complete and collects its exit status (see
	// Section 3.7.5 [Exit Status], page 44).

void	execute_cmds(t_minishell *mini)
{
	// parsing mini->cmd
		// 1 - int nbr_pipes = nbr_pipes(mini->cmd)
			// ....
		// 2 - nbr_cmds = nbr_pipes + 1;
			// fork(nbr_cmds)
		// while (...)
			// 3 - check which token is it (CMD, FLG, PP...)
				// 3.1 if (! HERDOC)
					
			
	//
	return ;
}
