script_folder="/media/vodo4ka/Data/BSUIR/2kurs/MOIS/RR/my-ostis-system/build/Release/generators"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
for v in PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export PATH="/home/vodo4ka/.conan2/p/b/sc-ma42bf7b2f1849d/p/bin:$PATH"
export LD_LIBRARY_PATH="/home/vodo4ka/.conan2/p/b/sc-ma42bf7b2f1849d/p/lib:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="/home/vodo4ka/.conan2/p/b/sc-ma42bf7b2f1849d/p/lib:$DYLD_LIBRARY_PATH"