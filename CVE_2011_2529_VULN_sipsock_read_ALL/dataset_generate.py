import sys
import os

list1 = ["int calculate_a = 5, calculate_b = 0;\n",
         "calculate_b = 7 * calculate_a + 2;\n",
         "calculate_a = 3 * calculate_b + 7;\n",
         "calculate_b = 4 * calculate_a - 5;\n",
         "printf(\"the sum is %d\", calculate_a + calculate_b);\n"]


def traceback(cur_name, target_folder, cur_level, tar_level, list_n, start, end, claim, text_content):

    if cur_level == tar_level:
        with open(os.path.join(target_folder, cur_name + ".c"), "w") as file_t:
            file_t.writelines(text_content)
        return

    if start > end:
        return

    if cur_level == 0:
        modified_content = text_content.copy()
        modified_content.insert(claim + cur_level, list_n[cur_level])
        traceback(cur_name, target_folder, cur_level + 1, tar_level, list_n, start, end, claim, modified_content)

        return

    for i in range(start, end):
        modified_content = text_content.copy()  # 避免修改原始的 text_content
        modified_content.insert(i + cur_level, list_n[cur_level])
        cur_name = cur_name + str(i) + " "
        traceback(cur_name, target_folder, cur_level + 1, tar_level, list_n, i + 1, end, claim, modified_content)
        cur_name = cur_name[:-(len(str(i)) + 1)]

    return


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    file_name = sys.argv[1]
    start_line = sys.argv[2]
    end_line = sys.argv[3]
    claim_line = sys.argv[4]

    folder_a = os.path.dirname(os.path.abspath(__file__))
    text_path = os.path.join(folder_a, file_name)

    folders = [os.path.join(folder_a, str(i) + "_" + file_name) for i in range(1, 5)]  # 生成四个文件夹路径
    for folder in folders:
        if not os.path.exists(folder):
            os.makedirs(folder)

    with open(text_path, "r", encoding="UTF-8") as file:
        text_c_content = file.readlines()

    traceback("", folders[0], 0, 2, list1, int(start_line), int(end_line), int(claim_line), text_c_content)
    traceback("", folders[1], 0, 3, list1, int(start_line), int(end_line), int(claim_line), text_c_content)
    traceback("", folders[2], 0, 4, list1, int(start_line), int(end_line), int(claim_line), text_c_content)
    traceback("", folders[3], 0, 5, list1, int(start_line), int(end_line), int(claim_line), text_c_content)

