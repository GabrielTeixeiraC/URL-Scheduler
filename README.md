# URL Scheduler
This program implements a URL scheduler, a module of a search engine responsible for defining the order in which URLs on the Internet should be crawled. Given a series of URLs from different hosts in the format 

    <protocol>://<host><path>?<query>#<fragment>
the program defines the order in which these URLs should be collected, following a depth-first collection strategy. A structure formed by a queue of lists was used, which collects known hosts first and then URLs with less depth.
## Compilation:
To compile the program, run:

    make all
## Usage:
The definition of the operations to be performed is up to the user, who must pass as a parameter to the program, through the command line, a text file containing the desired operations. The program recognizes the file name through regex and creates a file with the same name as the input file plus the suffix '-out', where the results of the desired operations will be stored.

The operations that the user can perform in the program are:
    
    ADD_URLS <quantity>: adds to the scheduler the URLs indicated in the following lines. The parameter <quantity> indicates how many lines will be read before the next command.

    ESCALONA_TUDO: schedules all URLs following the previously established rules. When scheduled, the URLs are displayed and removed from the list.

    ESCALONA <quantity>: limits the number of scheduled URLs.

    ESCALONA_HOST <host> <quantity>: only URLs from this host are scheduled.

    VER_HOST <host>: displays all URLs from the host, in priority order.

    LISTA_HOSTS: displays all hosts, following the order in which they were known.

    LIMPA_HOST <host>: clears the list of URLs from the host.
    
    LIMPA_TUDO: clears all hosts


## Example:
  ## Input:
    ADD_URLS 8
    http://github.com/collections/made-in-india/
    http://github.com/
    http://github.com/explore
    http://www.overleaf.com/project/
    http://www.overleaf.com/
    http://www.tudogostoso.com.br/receita/21217-brigadeiro-branco.html
    http://www.globo.com/
    http://www.tudogostoso.com.br/receita/1443-pao-de-queijo.html
    LISTA_HOSTS
    ESCALONA 2
    ESCALONA_HOST github.com 1
    VER_HOST tudogostoso.com.br
    LIMPA_HOST overleaf.com
    ESCALONA_TUDO
    ADD_URLS 1
    http://www.globo.com/
    LIMPA_TUDO
    LISTA_HOSTS

  ## Output:
    github.com
    overleaf.com
    tudogostoso.com.br
    globo.com
    http://github.com
    http://github.com/explore
    http://github.com/collections/made-in-india
    http://tudogostoso.com.br/receita/21217-brigadeiro-branco.html
    http://tudogostoso.com.br/receita/1443-pao-de-queijo.html
    http://tudogostoso.com.br/receita/21217-brigadeiro-branco.html
    http://tudogostoso.com.br/receita/1443-pao-de-queijo.html
    http://globo.com
