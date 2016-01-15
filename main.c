/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <time.h>
#include <string.h>

char * gettimestamp() {
    int oerrno = errno;
    time_t t = time(NULL);
    if (t == (time_t) -1) {
        error(EXIT_FAILURE, errno, "Unable to get a timestamp.");
    }
    
    char * ct = ctime(&t);
    if (ct == NULL) {
        error(EXIT_FAILURE, errno, "Unable to convert time to a string.");
    }
    // cut out the \n
    
    char * result = malloc(25 * sizeof(char));
    if (result == NULL) {
        error(EXIT_FAILURE, errno, "Memory allocation failure");
    }
    memset(result, 0, 25);

    memcpy(result, ct, 24);
    errno = oerrno;
    return result;
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        error(EXIT_FAILURE, errno, "%s Please specify the log file location", gettimestamp());
    }
    
    FILE * logfile = fopen(argv[1], "a");
    if (logfile == NULL) {
        error(EXIT_FAILURE, errno, "%s Unable to open the logfile", gettimestamp());
    }

    pid_t f = fork();
    if (f == 0) { // We are the child.
        return EXIT_SUCCESS;
    }
    if (f == -1) {
        int oerrno = errno;
        fprintf(logfile, "%s: %s fork() failed, %s", argv[0], gettimestamp(), strerror(oerrno));
        fclose(logfile);
        error(EXIT_FAILURE, oerrno, "%s fork() failed", gettimestamp());
    }
    // We are the parent.
    fprintf(logfile, "%s: %s fork() succeeded. Child PID is %i\n", argv[0], gettimestamp(), f);
    fclose(logfile);
    return EXIT_SUCCESS;
}
