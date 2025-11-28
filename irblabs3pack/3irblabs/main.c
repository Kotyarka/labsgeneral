#include "./include/functions.h"

int main() {

    UndoSystem undo_system;
    init_undo_system(&undo_system);

    LinkedList list = create_list();

    char filename[100];
    printf("Enter file path to load data: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    list = read_from_file(filename);

    int choice;
    char input[100];

    do {
        print_menu();

        if (fgets(input, sizeof(input), stdin)) {
            choice = atoi(input);

            switch (choice) {

                case 1:
                    display_all(&list);
                    break;

                case 2:
                    printf("Enter surname: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    search_by_surname(&list, input);
                    break;

                case 3: {
                    printf("Enter ID: ");
                    unsigned int id;
                    if (sscanf(input, "%u", &id) == 1)
                        search_by_id(&list, id);
                    else
                        printf("Invalid ID.\n");
                } break;

                case 4:
                    add_liver(&list, &undo_system);
                    break;

                case 5: {
                    printf("Enter resident ID to modify: ");
                    fgets(input, sizeof(input), stdin);
                    unsigned int id;
                    if (sscanf(input, "%u", &id) == 1)
                        modify_liver(&list, &undo_system, id);
                    else
                        printf("Invalid ID.\n");
                } break;

                case 6: {
                    printf("Enter resident ID to remove: ");
                    fgets(input, sizeof(input), stdin);
                    unsigned int id;
                    if (sscanf(input, "%u", &id) == 1)
                        remove_liver(&list, &undo_system, id);
                    else
                        printf("Invalid ID.\n");
                } break;

                case 7:
                    printf("Enter path to save: ");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    save_to_file(&list, input);
                    break;

                case 8:
                    undo_modifications(&list, &undo_system);
                    break;

                case 9:
                    printf("Exit.\n");
                    break;

                default:
                    printf("Invalid choice.\n");
            }
        }

    } while (choice != 9);

    delete_list(&list);
    clear_undo_system(&undo_system);

    return 0;
}