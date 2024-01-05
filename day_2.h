#ifndef DAY_2
#define DAY_2

void partOne2(char **data, size_t data_size) {
    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        char *c = data[i];

        int id_len = strchr(c, ':') - strchr(c, ' ');
        char comp[id_len];
        strncpy(comp, strchr(c, ' '), id_len);
        int id = atoi(comp);

        c = strchr(c, ':') + 1;
        int temp;
        char color[10] = "";
        int col_pos = 0;
        int possible = 1;
        while (*c != '\0' && possible) {
            if (isdigit(*c)) {
                int num_len = strchr(c, ' ') - c;
                char num[num_len];
                strncpy(num, c, num_len);
                temp = atoi(num);
                while (isdigit(*c)) c++;
            }
            else if (*c == ',' || *c == ';') {
                if (strcmp(color, "red") == 0 && temp > 12) possible = 0;
                else if (strcmp(color, "green") == 0 && temp > 13) possible = 0;
                else if (strcmp(color, "blue") == 0 && temp > 14) possible = 0;
                memset(color, 0, strlen(color));
                col_pos = 0;
            } else if (*c != ' ') {
                color[col_pos] = *c;
                col_pos++;
            }
            c++;
        }
        if (possible == 1) count += id;
    }
    printf("Part 1 Answer: %i\n", count);
}

void partTwo2(char **data, size_t data_size) {
    int count = 0;
    for (size_t i = 0; i < data_size; i++) {
        char *c = strchr(data[i], ':') + 1;
        int temp = 0, r = 0, g = 0, b = 0;
        char color[10] = "";
        int col_pos = 0;
        while (*c != '\0') {
            if (isdigit(*c)) {
                int num_len = strchr(c, ' ') - c;
                char num[num_len];
                strncpy(num, c, num_len);
                temp = atoi(num);
                while (isdigit(*c)) c++;
            }
            else if (*c == ',' || *c == ';') {
                if (strcmp(color, "red") == 0 && (temp >= r)) r = temp;
                else if (strcmp(color, "green") == 0 && (temp >= g)) g = temp;
                else if (strcmp(color, "blue") == 0 && (temp >= b)) b = temp;
                memset(color, 0, strlen(color));
                col_pos = 0;
            } else if (*c != ' ') {
                color[col_pos] = *c;
                col_pos++;
            }
            c++;
        }
        if (strcmp(color, "red") == 0 && (temp >= r)) r = temp;
        else if (strcmp(color, "green") == 0 && (temp >= g)) g = temp;
        else if (strcmp(color, "blue") == 0 && (temp >= b)) b = temp;

        count += r * g * b;
    }
    printf("Part 2 Answer: %i\n", count);
}

void dayTwo(char **data, size_t data_size) {
    partOne2(data, data_size);
    partTwo2(data, data_size);
}

#endif // DAY_2
