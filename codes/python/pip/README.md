# PIP 

## Package Management

```bash
pip list -v
python -m site
pip list | grep package_name
pip uninstall package_name
pip list --outdated
pip install --upgrade package_name
```

## Virtual Environment

```bash
# Create a virtual environment
python -m venv myenv

# Activate it (Linux/Mac)
source myenv/bin/activate

# Now pip installs will go to the virtual environment
```
